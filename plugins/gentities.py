class EntityField():
    def __init__(self, ffi, lib, field):
        self.ffi = ffi
        self.lib = lib
        self.name = ffi.string(field.name).decode()
        self.data_type = field.type
        self.offset = int(field.offset)
        self.flags = field.flags

    def __set__(self, obj, val):
        if self.flags & self.lib.FIELD_FLAG_READONLY:
            raise "Readonly attr"

        addr = obj.addr + self.offset

        if self.data_type == self.lib.FIELD_STRING:
            self.set_string_p(addr, val)
        elif self.data_type == self.lib.FIELD_INT:
            self.set_int(addr, val)
        elif self.data_type == self.lib.FIELD_FLOAT:
            self.set_float(addr, val)
        else:
            raise NotImplementedError

    def __get__(self, obj, objtype):
        addr = obj.addr + self.offset

        if self.data_type == self.lib.FIELD_STRING:
            if self.flags & self.lib.FIELD_FLAG_NOPTR:
                return self.get_string(addr)
            else:
                return self.get_string_p(addr)
        if self.data_type == self.lib.FIELD_FLOAT:
            return self.get_float(addr)
        if self.data_type == self.lib.FIELD_INT:
            return self.get_int(addr)
        if self.data_type & self.lib.FIELD_CLIENT:
            return self.get_client(addr)

        raise NotImplementedError

    def deref_ptr_from_ptr(self, ptr):
        x = self.ffi.cast("uintptr_t *", ptr)
        return x[0]

    def get_string(self, addr):
        a = self.ffi.cast("char *", addr)
        return self.ffi.string(a).decode()

    def set_string(self, addr, s):
        a = self.ffi.cast("char *", addr)
        for i, b in enumerate(s.encode()):
            a[i] = bytes([b])

    def get_string_p(self, addr):
        p = self.deref_ptr_from_ptr(addr)
        if p == 0:
            return None
        return self.get_string(p)

    def set_string_p(self, addr, s):
        p = self.deref_ptr_from_ptr(addr)
        self.set_string(p, s)

    def get_int(self, addr):
        p = self.ffi.cast("int *", addr)
        return int(p[0])

    def set_int(self, addr, val):
        p = self.ffi.cast("int *", addr)
        p[0] = int(val)

    def get_float(self, addr):
        p = self.ffi.cast("float *", addr)
        return float(p[0])

    def set_float(self, addr, val):
        p = self.ffi.cast("float *", addr)
        p[0] = float(val)

    def get_client(self, addr):
        p = self.deref_ptr_from_ptr(addr)
        if p == 0:
            return None
        return Gclient(self.ffi, self.lib, p)


class GclientNestedField:
    def __init__(self, addr):
        self.addr = addr


class Gclient:
    initialized = False

    def __init__(self, ffi, lib, addr):
        self.ffi = ffi
        self.lib = lib
        self.addr = addr

        if not Gclient.initialized:
            ptr = lib.gclient_get_fields()
            count = lib.gclient_get_fields_count()
            fields = ffi.cast(f"struct gentity_field [{count}]", ptr)

            for field in fields:
                path = ffi.string(field.name).decode().split(".")
                if len(path) == 2:
                    attr = path[1]
                    o = GclientNestedField
                    i = o(self.addr)
                    setattr(Gclient, path[0], i)
                elif len(path) == 1:
                    o = Gclient
                    attr = path[0]
                else:
                    continue  # TODO: something recursive here

                setattr(o, attr, EntityField(ffi, lib, field))

            Gclient.initialized = True


class Gentity:
    initialized = False

    def __init__(self, ffi, lib, addr):
        self.ffi = ffi
        self.lib = lib
        self.addr = addr

        if not Gentity.initialized:
            ptr = lib.gentity_get_fields()
            count = lib.gentity_get_fields_count()
            fields = ffi.cast(f"struct gentity_field [{count}]", ptr)

            for field in fields:
                setattr(Gentity, ffi.string(field.name).decode(),
                        EntityField(ffi, lib, field))

            Gentity.initialized = True


class Gentities:
    def __init__(self, ffi, lib):
        self.ffi = ffi
        self.lib = lib
        self.entities = None

    def update(self, gentities_ptr, num_gentities, gentity_size):
        self.entities = gentities_ptr & 0x7fffffffffff
        self.num_gentities = num_gentities
        self.gentity_size = gentity_size

    @property
    def initialized(self):
        return self.entities is not None

    def get(self, index):
        if not self.initialized:
            raise "Not initialized"

        if index > self.num_gentities:
            raise "index out of range"

        addr = self.entities + self.gentity_size * index

        return Gentity(self.ffi, self.lib, addr)
