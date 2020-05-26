class EasyApi:
    def __init__(self, ffi, lib):
        self.ffi = ffi
        self.lib = lib

    def _buffer(self, size: int):
        return self.ffi.new("char[]", size)

    def Print(self, s: str):
        self.lib.vm_Print(s.encode())

    def Error(self, s: str):
        self.lib.vm_Error(s.encode())

    def CvarGet(self, s: str) -> str:
        buf = self._buffer(256)
        self.lib.vm_Cvar_Get(s.encode(), buf, 256)
        return self.ffi.string(buf).decode()

    def CvarSet(self, s: str, val: str):
        self.lib.vm_Cvar_Set(s.encode(), val.encode())

    def GetConfigString(self, i: int) -> str:
        buf = self._buffer(1024)
        self.lib.vm_GetConfigString(i, buf, 1024)
        return self.ffi.string(buf).decode()

    def SetConfigString(self, i: int, s: str) -> str:
        self.lib.vm_SetConfigString(i, s.encode())

    def SendMsg(self, client: int, b: bytes) -> int:
        return self.lib.vm_SendMsg(client, b, len(b))

    def SendConsoleCommand(self, exec_when: int, cmd: str):
        self.lib.vm_SendConsoleCommand(exec_when, cmd.encode())

    def SendServerCommand(self, clientnum: int, cmd: str):
        self.lib.vm_SendServerCommand(clientnum, cmd.encode())

    def GetUserInfo(self, clientnum: int) -> str:
        buf = self._buffer(1024)
        self.lib.vm_GetUserInfo(clientnum, buf, 1024)
        return self.ffi.string(buf).decode()

    def SetUserInfo(self, clientnum: int, userinfo: str):
        self.lib.vm_SetUserInfo(clientnum, userinfo.encode())

    def DropClient(self, clientnum: int, reason: str, length: int):
        self.lib.vm_DropClient(clientnum, reason.encode(), length)

    def Milliseconds(self) -> int:
        return self.lib.vm_Milliseconds()

    def Argc(self) -> int:
        return self.lib.vm_Argc()

    def Argv(self, n: int) -> str:
        buf = self._buffer(1024)
        self.lib.vm_Argv(n, buf, 1024)
        return self.ffi.string(buf).decode()
