#define MAX_GENTITIES   ( 1 << 10 )
typedef enum {qfalse, qtrue}  qboolean;
typedef float vec_t;
typedef vec_t vec3_t[3];
typedef struct gentity_s gentity_t;
typedef unsigned char  byte;
typedef struct splinePath_s splinePath_t;


typedef enum {
        //============== general Quake services ==================

        G_PRINT,                // ( const char *string );
        // print message on the local console

        G_ERROR,                // ( const char *string );
        // abort the game

        G_MILLISECONDS,        // ( void );
        // get current time for profiling reasons
        // this should NOT be used for any game related tasks,
        // because it is not journaled

        // console variable interaction
        G_CVAR_REGISTER,        // ( vmCvar_t *vmCvar, const char *varName, const char *defaultValue, int flags );
        G_CVAR_UPDATE,        // ( vmCvar_t *vmCvar );
        G_CVAR_SET,                // ( const char *var_name, const char *value );
        G_CVAR_VARIABLE_INTEGER_VALUE,        // ( const char *var_name );

        G_CVAR_VARIABLE_STRING_BUFFER,        // ( const char *var_name, char *buffer, int bufsize );

        G_CVAR_LATCHEDVARIABLESTRINGBUFFER,

        G_ARGC,                        // ( void );
        // ClientCommand and ServerCommand parameter access

        G_ARGV,                        // ( int n, char *buffer, int bufferLength );

        G_FS_FOPEN_FILE,        // ( const char *qpath, fileHandle_t *file, fsMode_t mode );
        G_FS_READ,                // ( void *buffer, int len, fileHandle_t f );
        G_FS_WRITE,                // ( const void *buffer, int len, fileHandle_t f );
        G_FS_RENAME,
        G_FS_FCLOSE_FILE,                // ( fileHandle_t f );

        G_SEND_CONSOLE_COMMAND,        // ( const char *text );
        // add commands to the console as if they were typed in
        // for map changing, etc


        //=========== server specific functionality =============

        G_LOCATE_GAME_DATA,                // ( gentity_t *gEnts, int numGEntities, int sizeofGEntity_t,
        //                                                        playerState_t *clients, int sizeofGameClient );
        // the game needs to let the server system know where and how big the gentities
        // are, so it can look at them directly without going through an interface

        G_DROP_CLIENT,                // ( int clientNum, const char *reason );
        // kick a client off the server with a message

        G_SEND_SERVER_COMMAND,        // ( int clientNum, const char *fmt, ... );
        // reliably sends a command string to be interpreted by the given
        // client.  If clientNum is -1, it will be sent to all clients

        G_SET_CONFIGSTRING,        // ( int num, const char *string );
        // config strings hold all the index strings, and various other information
        // that is reliably communicated to all clients
        // All of the current configstrings are sent to clients when
        // they connect, and changes are sent to all connected clients.
        // All confgstrings are cleared at each level start.

        G_GET_CONFIGSTRING,        // ( int num, char *buffer, int bufferSize );

        G_GET_USERINFO,                // ( int num, char *buffer, int bufferSize );
        // userinfo strings are maintained by the server system, so they
        // are persistant across level loads, while all other game visible
        // data is completely reset

        G_SET_USERINFO,                // ( int num, const char *buffer );

        G_GET_SERVERINFO,        // ( char *buffer, int bufferSize );
        // the serverinfo info string has all the cvars visible to server browsers

        G_SET_BRUSH_MODEL,        // ( gentity_t *ent, const char *name );
        // sets mins and maxs based on the brushmodel name

        G_TRACE,        // ( trace_t *results, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int passEntityNum, int contentmask );
        // collision detection against all linked entities

        G_POINT_CONTENTS,        // ( const vec3_t point, int passEntityNum );
        // point contents against all linked entities

        G_IN_PVS,                        // ( const vec3_t p1, const vec3_t p2 );

        G_IN_PVS_IGNORE_PORTALS,        // ( const vec3_t p1, const vec3_t p2 );

        G_ADJUST_AREA_PORTAL_STATE,        // ( gentity_t *ent, qboolean open );

        G_AREAS_CONNECTED,        // ( int area1, int area2 );

        G_LINKENTITY,                // ( gentity_t *ent );
        // an entity will never be sent to a client or used for collision
        // if it is not passed to linkentity.  If the size, position, or
        // solidity changes, it must be relinked.

        G_UNLINKENTITY,                // ( gentity_t *ent );
        // call before removing an interactive entity

        G_ENTITIES_IN_BOX,        // ( const vec3_t mins, const vec3_t maxs, gentity_t **list, int maxcount );
        // EntitiesInBox will return brush models based on their bounding box,
        // so exact determination must still be done with EntityContact

        G_ENTITY_CONTACT,        // ( const vec3_t mins, const vec3_t maxs, const gentity_t *ent );
        // perform an exact check against inline brush models of non-square shape

        // access for bots to get and free a server client (FIXME?)
        G_BOT_ALLOCATE_CLIENT,        // ( int clientNum );

        G_BOT_FREE_CLIENT,        // ( int clientNum );

        G_GET_USERCMD,        // ( int clientNum, usercmd_t *cmd )

        G_GET_ENTITY_TOKEN,        // qboolean ( char *buffer, int bufferSize )
        // Retrieves the next string token from the entity spawn text, returning
        // false when all tokens have been parsed.
        // This should only be done at GAME_INIT time.

        G_FS_GETFILELIST,
        G_DEBUG_POLYGON_CREATE,
        G_DEBUG_POLYGON_DELETE,
        G_REAL_TIME,
        G_SNAPVECTOR,
// MrE:

        G_TRACECAPSULE,        // ( trace_t *results, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int passEntityNum, int contentmask );
        // collision detection using capsule against all linked entities

        G_ENTITY_CONTACTCAPSULE,        // ( const vec3_t mins, const vec3_t maxs, const gentity_t *ent );
        // perform an exact check against inline brush models of non-square shape
// done.

        G_GETTAG,

        G_REGISTERTAG,
        // Gordon: load a serverside tag

        G_REGISTERSOUND,        // xkan, 10/28/2002 - register the sound
        G_GET_SOUND_LENGTH,        // xkan, 10/28/2002 - get the length of the sound

        BOTLIB_SETUP = 200,                                // ( void );
        BOTLIB_SHUTDOWN,                                // ( void );
        BOTLIB_LIBVAR_SET,
        BOTLIB_LIBVAR_GET,
        BOTLIB_PC_ADD_GLOBAL_DEFINE,
        BOTLIB_START_FRAME,
        BOTLIB_LOAD_MAP,
        BOTLIB_UPDATENTITY,
        BOTLIB_TEST,

        BOTLIB_GET_SNAPSHOT_ENTITY,                // ( int client, int ent );
        BOTLIB_GET_CONSOLE_MESSAGE,                // ( int client, char *message, int size );
        BOTLIB_USER_COMMAND,                        // ( int client, usercmd_t *ucmd );

        BOTLIB_AAS_ENTITY_VISIBLE = 300,        //FIXME: remove
        BOTLIB_AAS_IN_FIELD_OF_VISION,                //FIXME: remove
        BOTLIB_AAS_VISIBLE_CLIENTS,                        //FIXME: remove
        BOTLIB_AAS_ENTITY_INFO,

        BOTLIB_AAS_INITIALIZED,
        BOTLIB_AAS_PRESENCE_TYPE_BOUNDING_BOX,
        BOTLIB_AAS_TIME,

        // Ridah
        BOTLIB_AAS_SETCURRENTWORLD,
        // done.

        BOTLIB_AAS_POINT_AREA_NUM,
        BOTLIB_AAS_TRACE_AREAS,
        BOTLIB_AAS_BBOX_AREAS,
        BOTLIB_AAS_AREA_CENTER,
        BOTLIB_AAS_AREA_WAYPOINT,

        BOTLIB_AAS_POINT_CONTENTS,
        BOTLIB_AAS_NEXT_BSP_ENTITY,
        BOTLIB_AAS_VALUE_FOR_BSP_EPAIR_KEY,
        BOTLIB_AAS_VECTOR_FOR_BSP_EPAIR_KEY,
        BOTLIB_AAS_FLOAT_FOR_BSP_EPAIR_KEY,
        BOTLIB_AAS_INT_FOR_BSP_EPAIR_KEY,

        BOTLIB_AAS_AREA_REACHABILITY,
        BOTLIB_AAS_AREA_LADDER,

        BOTLIB_AAS_AREA_TRAVEL_TIME_TO_GOAL_AREA,

        BOTLIB_AAS_SWIMMING,
        BOTLIB_AAS_PREDICT_CLIENT_MOVEMENT,

        // Ridah, route-tables
        BOTLIB_AAS_RT_SHOWROUTE,
        //BOTLIB_AAS_RT_GETHIDEPOS,
        //BOTLIB_AAS_FINDATTACKSPOTWITHINRANGE,
        BOTLIB_AAS_NEARESTHIDEAREA,
        BOTLIB_AAS_LISTAREASINRANGE,
        BOTLIB_AAS_AVOIDDANGERAREA,
        BOTLIB_AAS_RETREAT,
        BOTLIB_AAS_ALTROUTEGOALS,
        BOTLIB_AAS_SETAASBLOCKINGENTITY,
        BOTLIB_AAS_RECORDTEAMDEATHAREA,
        // done.

        BOTLIB_EA_SAY = 400,
        BOTLIB_EA_SAY_TEAM,
        BOTLIB_EA_USE_ITEM,
        BOTLIB_EA_DROP_ITEM,
        BOTLIB_EA_USE_INV,
        BOTLIB_EA_DROP_INV,
        BOTLIB_EA_GESTURE,
        BOTLIB_EA_COMMAND,

        BOTLIB_EA_SELECT_WEAPON,
        BOTLIB_EA_TALK,
        BOTLIB_EA_ATTACK,
        BOTLIB_EA_RELOAD,
        BOTLIB_EA_USE,
        BOTLIB_EA_RESPAWN,
        BOTLIB_EA_JUMP,
        BOTLIB_EA_DELAYED_JUMP,
        BOTLIB_EA_CROUCH,
        BOTLIB_EA_WALK,
        BOTLIB_EA_MOVE_UP,
        BOTLIB_EA_MOVE_DOWN,
        BOTLIB_EA_MOVE_FORWARD,
        BOTLIB_EA_MOVE_BACK,
        BOTLIB_EA_MOVE_LEFT,
        BOTLIB_EA_MOVE_RIGHT,
        BOTLIB_EA_MOVE,
        BOTLIB_EA_VIEW,
        // START        xkan, 9/16/2002
        BOTLIB_EA_PRONE,
        // END                xkan, 9/16/2002

        BOTLIB_EA_END_REGULAR,
        BOTLIB_EA_GET_INPUT,
        BOTLIB_EA_RESET_INPUT,


        BOTLIB_AI_LOAD_CHARACTER = 500,
        BOTLIB_AI_FREE_CHARACTER,
        BOTLIB_AI_CHARACTERISTIC_FLOAT,
        BOTLIB_AI_CHARACTERISTIC_BFLOAT,
        BOTLIB_AI_CHARACTERISTIC_INTEGER,
        BOTLIB_AI_CHARACTERISTIC_BINTEGER,
        BOTLIB_AI_CHARACTERISTIC_STRING,

        BOTLIB_AI_ALLOC_CHAT_STATE,
        BOTLIB_AI_FREE_CHAT_STATE,
        BOTLIB_AI_QUEUE_CONSOLE_MESSAGE,
        BOTLIB_AI_REMOVE_CONSOLE_MESSAGE,
        BOTLIB_AI_NEXT_CONSOLE_MESSAGE,
        BOTLIB_AI_NUM_CONSOLE_MESSAGE,
        BOTLIB_AI_INITIAL_CHAT,
        BOTLIB_AI_REPLY_CHAT,
        BOTLIB_AI_CHAT_LENGTH,
        BOTLIB_AI_ENTER_CHAT,
        BOTLIB_AI_STRING_CONTAINS,
        BOTLIB_AI_FIND_MATCH,
        BOTLIB_AI_MATCH_VARIABLE,
        BOTLIB_AI_UNIFY_WHITE_SPACES,
        BOTLIB_AI_REPLACE_SYNONYMS,
        BOTLIB_AI_LOAD_CHAT_FILE,
        BOTLIB_AI_SET_CHAT_GENDER,
        BOTLIB_AI_SET_CHAT_NAME,

        BOTLIB_AI_RESET_GOAL_STATE,
        BOTLIB_AI_RESET_AVOID_GOALS,
        BOTLIB_AI_PUSH_GOAL,
        BOTLIB_AI_POP_GOAL,
        BOTLIB_AI_EMPTY_GOAL_STACK,
        BOTLIB_AI_DUMP_AVOID_GOALS,
        BOTLIB_AI_DUMP_GOAL_STACK,
        BOTLIB_AI_GOAL_NAME,
        BOTLIB_AI_GET_TOP_GOAL,
        BOTLIB_AI_GET_SECOND_GOAL,
        BOTLIB_AI_CHOOSE_LTG_ITEM,
        BOTLIB_AI_CHOOSE_NBG_ITEM,
        BOTLIB_AI_TOUCHING_GOAL,
        BOTLIB_AI_ITEM_GOAL_IN_VIS_BUT_NOT_VISIBLE,
        BOTLIB_AI_GET_LEVEL_ITEM_GOAL,
        BOTLIB_AI_AVOID_GOAL_TIME,
        BOTLIB_AI_INIT_LEVEL_ITEMS,
        BOTLIB_AI_UPDATE_ENTITY_ITEMS,
        BOTLIB_AI_LOAD_ITEM_WEIGHTS,
        BOTLIB_AI_FREE_ITEM_WEIGHTS,
        BOTLIB_AI_SAVE_GOAL_FUZZY_LOGIC,
        BOTLIB_AI_ALLOC_GOAL_STATE,
        BOTLIB_AI_FREE_GOAL_STATE,

        BOTLIB_AI_RESET_MOVE_STATE,
        BOTLIB_AI_MOVE_TO_GOAL,
        BOTLIB_AI_MOVE_IN_DIRECTION,
        BOTLIB_AI_RESET_AVOID_REACH,
        BOTLIB_AI_RESET_LAST_AVOID_REACH,
        BOTLIB_AI_REACHABILITY_AREA,
        BOTLIB_AI_MOVEMENT_VIEW_TARGET,
        BOTLIB_AI_ALLOC_MOVE_STATE,
        BOTLIB_AI_FREE_MOVE_STATE,
        BOTLIB_AI_INIT_MOVE_STATE,
        // Ridah
        BOTLIB_AI_INIT_AVOID_REACH,
        // done.

        BOTLIB_AI_CHOOSE_BEST_FIGHT_WEAPON,
        BOTLIB_AI_GET_WEAPON_INFO,
        BOTLIB_AI_LOAD_WEAPON_WEIGHTS,
        BOTLIB_AI_ALLOC_WEAPON_STATE,
        BOTLIB_AI_FREE_WEAPON_STATE,
        BOTLIB_AI_RESET_WEAPON_STATE,

        BOTLIB_AI_GENETIC_PARENTS_AND_CHILD_SELECTION,
        BOTLIB_AI_INTERBREED_GOAL_FUZZY_LOGIC,
        BOTLIB_AI_MUTATE_GOAL_FUZZY_LOGIC,
        BOTLIB_AI_GET_NEXT_CAMP_SPOT_GOAL,
        BOTLIB_AI_GET_MAP_LOCATION_GOAL,
        BOTLIB_AI_NUM_INITIAL_CHATS,
        BOTLIB_AI_GET_CHAT_MESSAGE,
        BOTLIB_AI_REMOVE_FROM_AVOID_GOALS,
        BOTLIB_AI_PREDICT_VISIBLE_POSITION,

        BOTLIB_AI_SET_AVOID_GOAL_TIME,
        BOTLIB_AI_ADD_AVOID_SPOT,
        BOTLIB_AAS_ALTERNATIVE_ROUTE_GOAL,
        BOTLIB_AAS_PREDICT_ROUTE,
        BOTLIB_AAS_POINT_REACHABILITY_AREA_INDEX,

        BOTLIB_PC_LOAD_SOURCE,
        BOTLIB_PC_FREE_SOURCE,
        BOTLIB_PC_READ_TOKEN,
        BOTLIB_PC_SOURCE_FILE_AND_LINE,
        BOTLIB_PC_UNREAD_TOKEN,

        PB_STAT_REPORT,

        // zinx
        G_SENDMESSAGE,
        G_MESSAGESTATUS,
        // -zinx
} gameImport_t;

typedef enum {
        ET_GENERAL,
        ET_PLAYER,
        ET_ITEM,
        ET_MISSILE,
        ET_MOVER,
        ET_BEAM,
        ET_PORTAL,
        ET_SPEAKER,
        ET_PUSH_TRIGGER,
        ET_TELEPORT_TRIGGER,
        ET_INVISIBLE,
        ET_CONCUSSIVE_TRIGGER,  // JPW NERVE trigger for concussive dust particles
        ET_OID_TRIGGER,         // DHM - Nerve :: Objective Info Display
        ET_EXPLOSIVE_INDICATOR, // NERVE - SMF

        //---- (SA) Wolf
        ET_EXPLOSIVE,           // brush that will break into smaller bits when damaged
        ET_EF_SPOTLIGHT,
        ET_ALARMBOX,
        ET_CORONA,
        ET_TRAP,

        ET_GAMEMODEL,           // misc_gamemodel.  similar to misc_model, but it's a dynamic model so we have LOD
        ET_FOOTLOCKER,  //----(SA)        added
        //---- end

        ET_FLAMEBARREL,
        ET_FP_PARTS,

        // FIRE PROPS
        ET_FIRE_COLUMN,
        ET_FIRE_COLUMN_SMOKE,
        ET_RAMJET,

        ET_FLAMETHROWER_CHUNK,      // DHM - NERVE :: Used in server side collision detection for flamethrower

        ET_EXPLO_PART,

        ET_PROP,

        ET_AI_EFFECT,

        ET_CAMERA,
        ET_MOVERSCALED,

        ET_CONSTRUCTIBLE_INDICATOR,
        ET_CONSTRUCTIBLE,
        ET_CONSTRUCTIBLE_MARKER,
        ET_BOMB,
        ET_WAYPOINT,
        ET_BEAM_2,
        ET_TANK_INDICATOR,
        ET_TANK_INDICATOR_DEAD,
        // Start - TAT - 8/29/2002
        // An indicator object created by the bot code to show where the bots are moving to
        ET_BOTGOAL_INDICATOR,
        // End - TA - 8/29/2002
        ET_CORPSE,              // Arnout: dead player
        ET_SMOKER,              // Arnout: target_smoke entity

        ET_TEMPHEAD,            // Gordon: temporary head for clients for bullet traces
        ET_MG42_BARREL,         // Arnout: MG42 barrel
        ET_TEMPLEGS,            // Arnout: temporary leg for clients for bullet traces
        ET_TRIGGER_MULTIPLE,
        ET_TRIGGER_FLAGONLY,
        ET_TRIGGER_FLAGONLY_MULTIPLE,
        ET_GAMEMANAGER,
        ET_AAGUN,
        ET_CABINET_H,
        ET_CABINET_A,
        ET_HEALER,
        ET_SUPPLIER,

        ET_LANDMINE_HINT,       // Gordon: landmine hint for botsetgoalstate filter
        ET_ATTRACTOR_HINT,      // Gordon: attractor hint for botsetgoalstate filter
        ET_SNIPER_HINT,         // Gordon: sniper hint for botsetgoalstate filter
        ET_LANDMINESPOT_HINT,   // Gordon: landminespot hint for botsetgoalstate filter

        ET_COMMANDMAP_MARKER,

        ET_WOLF_OBJECTIVE,

        ET_EVENTS               // any of the EV_* events can be added freestanding
                                                        // by setting eType to ET_EVENTS + eventNum
                                                        // this avoids having to set eFlags and eventNum
} entityType_t;

typedef enum {
        TR_STATIONARY,
        TR_INTERPOLATE,             // non-parametric, but interpolate between snapshots
        TR_LINEAR,
        TR_LINEAR_STOP,
        TR_LINEAR_STOP_BACK,        //----(SA)        added.  so reverse movement can be different than forward
        TR_SINE,                    // value = base + sin( time / duration ) * delta
        TR_GRAVITY,
        // Ridah
        TR_GRAVITY_LOW,
        TR_GRAVITY_FLOAT,           // super low grav with no gravity acceleration (floating feathers/fabric/leaves/...)
        TR_GRAVITY_PAUSED,          //----(SA)        has stopped, but will still do a short trace to see if it should be switched back to TR_GRAVITY
        TR_ACCELERATE,
        TR_DECCELERATE,
        // Gordon
        TR_SPLINE,
        TR_LINEAR_PATH
} trType_t;

typedef struct {
        trType_t trType;
        int trTime;
        int trDuration;             // if non 0, trTime + trDuration = stop time
//----(SA)        removed
        vec3_t trBase;
        vec3_t trDelta;             // velocity, etc
//----(SA)        removed
} trajectory_t;

typedef enum
{
        AISTATE_RELAXED,
        AISTATE_QUERY,
        AISTATE_ALERT,
        AISTATE_COMBAT,

        MAX_AISTATES
} aistateEnum_t;

typedef struct entityState_s
{
	int number;             // entity index
	entityType_t eType;     // entityType_t
	int eFlags;

	trajectory_t pos;       // for calculating position
	trajectory_t apos;      // for calculating angles

	int time;
	int time2;

	vec3_t origin;
	vec3_t origin2;

	vec3_t angles;
	vec3_t angles2;

	int otherEntityNum;     // shotgun sources, etc
	int otherEntityNum2;

	int groundEntityNum;    // -1 = in air

	int constantLight;      // r + (g<<8) + (b<<16) + (intensity<<24)
	int dl_intensity;       // used for coronas
	int loopSound;          // constantly loop this sound

	int modelindex;
	int modelindex2;
	int clientNum;          // 0 to (MAX_CLIENTS - 1), for players and corpses
	int frame;

	int solid;              // for client side prediction, trap_linkentity sets this properly

	// old style events, in for compatibility only
	int event;
	int eventParm;

	int eventSequence;      // pmove generated events
	int events[4];
	int eventParms[4];

	// for players
	int powerups;           // bit flags. Used to store entState_t for non-player entities (so we know to draw them translucent clientsided)
	int weapon;             // determines weapon and flash model, etc
	int legsAnim;           // mask off ANIM_TOGGLEBIT
	int torsoAnim;          // mask off ANIM_TOGGLEBIT

	int density;            // for particle effects

	int dmgFlags;           // to pass along additional information for damage effects for players/ Also used for cursorhints for non-player entities

	int onFireStart, onFireEnd;

	int nextWeapon;
	int teamNum;

	int effect1Time, effect2Time, effect3Time;

	aistateEnum_t aiState;
	int animMovetype;       // clients can't derive movetype of other clients for anim scripting system
} entityState_t;

typedef struct {
//        entityState_t        s;                                // communicated by server to clients

        qboolean linked;                // qfalse if not in any good cluster
        int linkcount;

        int svFlags;                    // SVF_NOCLIENT, SVF_BROADCAST, etc
        int singleClient;               // only send to this client when SVF_SINGLECLIENT is set

        qboolean bmodel;                // if false, assume an explicit mins / maxs bounding box
                                                                        // only set by trap_SetBrushModel
        vec3_t mins, maxs;
        int contents;                   // CONTENTS_TRIGGER, CONTENTS_SOLID, CONTENTS_BODY, etc
                                                                        // a non-solid entity should set to 0

        vec3_t absmin, absmax;          // derived from mins/maxs and origin + rotation

        // currentOrigin will be used for all collision detection and world linking.
        // it will not necessarily be the same as the trajectory evaluation for the current
        // time, because each entity must be moved one at a time after time is advanced
        // to avoid simultanious collision issues
        vec3_t currentOrigin;
        vec3_t currentAngles;

        // when a trace call is made and passEntityNum != ENTITYNUM_NONE,
        // an ent will be excluded from testing if:
        // ent->s.number == passEntityNum        (don't interact with self)
        // ent->s.ownerNum = passEntityNum        (don't interact with your own missiles)
        // entity[ent->s.ownerNum].ownerNum = passEntityNum        (don't interact with other missiles from owner)
        int ownerNum;
        int eventTime;

        int worldflags;             // DHM - Nerve

        qboolean snapshotCallback;
} entityShared_t;

typedef enum {
        MOVER_POS1,
        MOVER_POS2,
        MOVER_POS3,
        MOVER_1TO2,
        MOVER_2TO1,
        // JOSEPH 1-26-00
        MOVER_2TO3,
        MOVER_3TO2,
        // END JOSEPH

        // Rafael
        MOVER_POS1ROTATE,
        MOVER_POS2ROTATE,
        MOVER_1TO2ROTATE,
        MOVER_2TO1ROTATE
} moverState_t;

typedef struct cplane_s {
        vec3_t normal;
        float dist;
        byte type;              // for fast side tests: 0,1,2 = axial, 3 = nonaxial
        byte signbits;          // signx + (signy<<1) + (signz<<2), used as lookup during collision
        byte pad[2];
} cplane_t;

typedef struct {
        qboolean allsolid;      // if true, plane is not valid
        qboolean startsolid;    // if true, the initial point was in a solid area
        float fraction;         // time completed, 1.0 = didn't hit anything
        vec3_t endpos;          // final position
        cplane_t plane;         // surface normal at impact, transformed to world space
        int surfaceFlags;           // surface hit
        int contents;           // contents on other side of surface hit
        int entityNum;          // entity the contacted sirface is a part of
} trace_t;

typedef enum {
        MOD_UNKNOWN,
        MOD_MACHINEGUN,
        MOD_BROWNING,
        MOD_MG42,
        MOD_GRENADE,
        MOD_ROCKET,

        // (SA) modified wolf weap mods
        MOD_KNIFE,
        MOD_LUGER,
        MOD_COLT,
        MOD_MP40,
        MOD_THOMPSON,
        MOD_STEN,
        MOD_GARAND,
        MOD_SNOOPERSCOPE,
        MOD_SILENCER,   //----(SA)
        MOD_FG42,
        MOD_FG42SCOPE,
        MOD_PANZERFAUST,
        MOD_GRENADE_LAUNCHER,
        MOD_FLAMETHROWER,
        MOD_GRENADE_PINEAPPLE,
        MOD_CROSS,
        // end

        MOD_MAPMORTAR,
        MOD_MAPMORTAR_SPLASH,

        MOD_KICKED,
        MOD_GRABBER,

        MOD_DYNAMITE,
        MOD_AIRSTRIKE, // JPW NERVE
        MOD_SYRINGE,    // JPW NERVE
        MOD_AMMO,   // JPW NERVE
        MOD_ARTY,   // JPW NERVE

        MOD_WATER,
        MOD_SLIME,
        MOD_LAVA,
        MOD_CRUSH,
        MOD_TELEFRAG,
        MOD_FALLING,
        MOD_SUICIDE,
        MOD_TARGET_LASER,
        MOD_TRIGGER_HURT,
        MOD_EXPLOSIVE,

        MOD_CARBINE,
        MOD_KAR98,
        MOD_GPG40,
        MOD_M7,
        MOD_LANDMINE,
        MOD_SATCHEL,
        MOD_TRIPMINE,
        MOD_SMOKEBOMB,
        MOD_MOBILE_MG42,
        MOD_SILENCED_COLT,
        MOD_GARAND_SCOPE,

        MOD_CRUSH_CONSTRUCTION,
        MOD_CRUSH_CONSTRUCTIONDEATH,
        MOD_CRUSH_CONSTRUCTIONDEATH_NOATTACKER,

        MOD_K43,
        MOD_K43_SCOPE,

        MOD_MORTAR,

        MOD_AKIMBO_COLT,
        MOD_AKIMBO_LUGER,
        MOD_AKIMBO_SILENCEDCOLT,
        MOD_AKIMBO_SILENCEDLUGER,

        MOD_SMOKEGRENADE,

        // RF
        MOD_SWAP_PLACES,

        // OSP -- keep these 2 entries last
        MOD_SWITCHTEAM,

        MOD_NUM_MODS

} meansOfDeath_t;

typedef enum {
        IT_BAD,
        IT_WEAPON,              // EFX: rotate + upscale + minlight

        IT_AMMO,                // EFX: rotate
        IT_ARMOR,               // EFX: rotate + minlight
        IT_HEALTH,              // EFX: static external sphere + rotating internal
        IT_HOLDABLE,            // single use, holdable item
                                                        // EFX: rotate + bob
        IT_KEY,
        IT_TREASURE,            // gold bars, etc.  things that can be picked up and counted for a tally at end-level
        IT_TEAM,
} itemType_t;

typedef struct gitem_s {
        char        *classname; // spawning name
        char        *pickup_sound;
        char        *world_model[3];

        char        *icon;
        char        *ammoicon;
        char        *pickup_name;   // for printing on pickup

        int quantity;               // for ammo how much, or duration of powerup (value not necessary for ammo/health.  that value set in gameskillnumber[] below)
        itemType_t giType;          // IT_* flags

        int giTag;

        int giAmmoIndex;            // type of weapon ammo this uses.  (ex. WP_MP40 and WP_LUGER share 9mm ammo, so they both have WP_LUGER for giAmmoIndex)
        int giClipIndex;            // which clip this weapon uses.  this allows the sniper rifle to use the same clip as the garand, etc.

        char        *precaches;     // string of all models and images this item will use
        char        *sounds;        // string of all sounds this item will use

//        int                        gameskillnumber[5];
} gitem_t;

typedef struct
{
        char    *actionString;
        qboolean ( *actionFunc )( gentity_t *ent, char *params );
        int hash;
} g_script_stack_action_t;

typedef struct
{
        //
        // set during script parsing
        g_script_stack_action_t     *action;            // points to an action to perform
        char                        *params;
} g_script_stack_item_t;

typedef struct
{
        g_script_stack_item_t items[196];
        int numItems;
} g_script_stack_t;

typedef struct
{
        int eventNum;                           // index in scriptEvents[]
        char                *params;            // trigger targetname, etc
        g_script_stack_t stack;
} g_script_event_t;

typedef struct
{
        int scriptStackHead, scriptStackChangeTime;
        int scriptEventIndex;       // current event containing stack of actions to perform
        // scripting system variables
        int scriptId;                   // incremented each time the script changes
        int scriptFlags;
        int actionEndTime;              // time to end the current action
        char    *animatingParams;       // Gordon: read 8 lines up for why i love this code ;)
} g_script_status_t;

typedef enum {
        STATE_DEFAULT,          // ent is linked, can be used and is solid
        STATE_INVISIBLE,        // ent is unlinked, can't be used, doesn't think and is not solid
        STATE_UNDERCONSTRUCTION // ent is being constructed
} entState_t;

typedef struct {
        char name[64];
        vec3_t origin;
} pathCorner_t;

typedef struct {
        vec3_t start;
        vec3_t v_norm;
        float length;
} splineSegment_t;

struct splinePath_s {
        pathCorner_t point;

        char strTarget[64];

        splinePath_t*   next;
        splinePath_t*   prev;

        pathCorner_t controls[4];
        int numControls;
        splineSegment_t segments[16];

        float length;

        qboolean isStart;
        qboolean isEnd;
};

typedef struct g_constructible_stats_s {
        float chargebarreq;
        float constructxpbonus;
        float destructxpbonus;
        int health;
        int weaponclass;
        int duration;
} g_constructible_stats_t;

typedef struct playerState_s
{
        int commandTime;            // cmd->serverTime of last executed command
        int pm_type;
        int bobCycle;               // for view bobbing and footstep generation
        int pm_flags;               // ducked, jump_held, etc
        int pm_time;

        vec3_t origin;
        vec3_t velocity;
        int weaponTime;
        int weaponDelay;            // for weapons that don't fire immediately when 'fire' is hit (grenades, venom, ...)
        int grenadeTimeLeft;        // for delayed grenade throwing.  this is set to a #define for grenade
        // lifetime when the attack button goes down, then when attack is released
        // this is the amount of time left before the grenade goes off (or if it
        // gets to 0 while in players hand, it explodes)

        int gravity;
        float leanf;                // amount of 'lean' when player is looking around corner //----(SA) added

        int speed;
        int delta_angles[3];            // add to command angles to get view direction
        // changed by spawns, rotating objects, and teleporters

        int groundEntityNum;        // ENTITYNUM_NONE = in air

        int legsTimer;              // don't change low priority animations until this runs out
        int legsAnim;               // mask off ANIM_TOGGLEBIT

        int torsoTimer;             // don't change low priority animations until this runs out
        int torsoAnim;              // mask off ANIM_TOGGLEBIT

        int movementDir;            // a number 0 to 7 that represents the reletive angle
        // of movement to the view angle (axial and diagonals)
        // when at rest, the value will remain unchanged
        // used to twist the legs during strafing

        int eFlags;                 // copied to entityState_t->eFlags

        int eventSequence;          // pmove generated events
        int events[4];
        int eventParms[4];
        int oldEventSequence;       // so we can see which events have been added since we last converted to entityState_t

        int externalEvent;          // events set on player from another source
        int externalEventParm;
        int externalEventTime;

        int clientNum;              // ranges from 0 to MAX_CLIENTS-1

        // weapon info
        int weapon;                 // copied to entityState_t->weapon
        int weaponstate;

        // item info
        int item;

        vec3_t viewangles;          // for fixed views
        int viewheight;

        // damage feedback
        int damageEvent;            // when it changes, latch the other parms
        int damageYaw;
        int damagePitch;
        int damageCount;

        int stats[16];
        int persistant[16];                 // stats that aren't cleared on death
        int powerups[16];                     // level.time that the powerup runs out
        int ammo[64];                          // total amount of ammo
        int ammoclip[64];                      // ammo in clip
        int holdable[16];
        int holding;                                    // the current item in holdable[] that is selected (held)
        int weapons[64 / (sizeof(int) * 8)];   // 64 bits for weapons held

        // allow for individual bounding boxes
        vec3_t mins, maxs;
        float crouchMaxZ;
        float crouchViewHeight, standViewHeight, deadViewHeight;
        // variable movement speed
        float runSpeedScale, sprintSpeedScale, crouchSpeedScale;

        // view locking for mg42
        int viewlocked;
        int viewlocked_entNum;

        float friction;

        int nextWeapon;
        int teamNum;                        // doesn't seem to be communicated over the net

        // RF, burning effect is required for view blending effect
        int onFireStart;

        int serverCursorHint;               // what type of cursor hint the server is dictating
        int serverCursorHintVal;            // a value (0-255) associated with the above

        trace_t serverCursorHintTrace;      // not communicated over net, but used to store the current server-side cursorhint trace

        // ----------------------------------------------------------------------
        // So to use persistent variables here, which don't need to come from the server,
        // we could use a marker variable, and use that to store everything after it
        // before we read in the new values for the predictedPlayerState, then restore them
        // after copying the structure recieved from the server.

        // use the pmoveExt_t structure in bg_public.h to store this kind of data now (persistant on client, not network transmitted)

        int ping;                       // server to game info for scoreboard
        int pmove_framecount;
        int entityEventSequence;

        int sprintExertTime;

        // value for all multiplayer classes with regenerating "class weapons" -- ie LT artillery, medic medpack, engineer build points, etc
        int classWeaponTime;            // DOES get send over the network
        int jumpTime;                   // used in MP to prevent jump accel

        int weapAnim;                   // mask off ANIM_TOGGLEBIT, DOES get send over the network

        qboolean releasedFire;

        float aimSpreadScaleFloat;      // the server-side aimspreadscale that lets it track finer changes but still only
        // transmit the 8bit int to the client
        int aimSpreadScale;             // 0 - 255 increases with angular movement. DOES get send over the network
        int lastFireTime;               // used by server to hold last firing frame briefly when randomly releasing trigger (AI)
                                        // Set, but never used?

        int quickGrenTime;              // unused
        int leanStopDebounceTime;       // unused

        // seems like heat and aimspread could be tied together somehow, however, they (appear to) change at different rates and
        // I can't currently see how to optimize this to one server->client transmission "weapstatus" value.
        int weapHeat[64];          // some weapons can overheat.  this tracks (server-side) how hot each weapon currently is.
        int curWeapHeat;                    // value for the currently selected weapon (for transmission to client). DOES get send over the network
        int identifyClient;
        int identifyClientHealth;

        aistateEnum_t aiState;
} playerState_t;

struct gentity_s
{
        entityState_t s;                // communicated by server to clients
        entityShared_t r;               // shared by both the server system and game

        // DO NOT MODIFY ANYTHING ABOVE THIS, THE SERVER
        // EXPECTS THE FIELDS IN THAT ORDER!
        //================================

        struct gclient_s *client;               // NULL if not a client

        qboolean inuse;

        vec3_t instantVelocity;         // per entity instantaneous velocity, set per frame

        char *classname;                // set in QuakeEd
        int spawnflags;                 // set in QuakeEd

        qboolean neverFree;             // if true, FreeEntity will only unlink
        // bodyque uses this

        int flags;                      // FL_* variables

        char *model;
        char *model2;
        int freetime;                   // level.time when the object was freed

        int eventTime;                  // events will be cleared EVENT_VALID_MSEC after set
        qboolean freeAfterEvent;
        qboolean unlinkAfterEvent;

        qboolean physicsObject;         // if true, it can be pushed by movers and fall off edges
        // all game items are physicsObjects,
        float physicsBounce;            // 1.0 = continuous bounce, 0.0 = no bounce
        int clipmask;                   // brushes with this content value will be collided against
        // when moving.  items and corpses do not collide against
        // players, for instance

        int realClipmask;               // use these to backup the contents value when we go to state under construction
        int realContents;
        qboolean realNonSolidBModel;    // For script_movers with spawnflags 2 set

        // movers
        moverState_t moverState;
        int soundPos1;
        int sound1to2;
        int sound2to1;
        int soundPos2;
        int soundLoop;
        int sound2to3;
        int sound3to2;
        int soundPos3;

        int soundSoftopen;
        int soundSoftendo;
        int soundSoftclose;
        int soundSoftendc;

        gentity_t *parent;
        gentity_t *nextTrain;
        gentity_t *prevTrain;
        vec3_t pos1, pos2, pos3;

        char *message;

        int timestamp;              // body queue sinking, etc

        float angle;                // set in editor, -1 = up, -2 = down
        char *target;

        char *targetname;
        int targetnamehash;         // adding a hash for this for faster lookups

        char *team;
        gentity_t *target_ent;

        float speed;
        float closespeed;           // for movers that close at a different speed than they open
        vec3_t movedir;

        int gDuration;
        int gDurationBack;
        vec3_t gDelta;
        vec3_t gDeltaBack;

        int nextthink;
        void (*free)(gentity_t *self);
        void (*think)(gentity_t *self);
        void (*reached)(gentity_t *self);           // movers call this when hitting endpoint
        void (*blocked)(gentity_t *self, gentity_t *other);
        void (*touch)(gentity_t *self, gentity_t *other, trace_t *trace);
        void (*use)(gentity_t *self, gentity_t *other, gentity_t *activator);
        void (*pain)(gentity_t *self, gentity_t *attacker, int damage, vec3_t point);
        void (*die)(gentity_t *self, gentity_t *inflictor, gentity_t *attacker, int damage, int mod);

        int pain_debounce_time;
        int fly_sound_debounce_time;            // wind tunnel

        int health;

        qboolean takedamage;

        int damage;
        int splashDamage;           // quad will increase this without increasing radius
        int splashRadius;
        int methodOfDeath;
        int splashMethodOfDeath;

        int count;

        gentity_t *chain;
        gentity_t *enemy;
        gentity_t *activator;
        gentity_t *teamchain;       // next entity in team
        gentity_t *teammaster;      // master of the team

        meansOfDeath_t deathType;

        int watertype;
        int waterlevel;

        int noise_index;

        // timing variables
        float wait;
        float random;

        // sniper variable
        // sniper uses delay, random, radius
        int radius;
        float delay;

        int TargetFlag;
        float duration;
        vec3_t rotate;
        vec3_t TargetAngles;
        gitem_t *item;              // for bonus items

        // Ridah, AI fields
        char *aiName;
        void (*AIScript_AlertEntity)(gentity_t *ent);

        char *aiSkin;

        vec3_t dl_color;
        char *dl_stylestring;
        char *dl_shader;
        int dl_atten;

        int key;                    // used by:  target_speaker->nopvs,

        qboolean active;

        // mg42
        float harc;
        float varc;

        int props_frame_state;

        int missionLevel;               // mission we are currently trying to complete
        // gets reset each new level
        int start_size;
        int end_size;

        qboolean isProp;                // teamkilled or not

        int mg42BaseEnt;

        char *spawnitem;

        int flameQuota, flameQuotaTime, flameBurnEnt;

        int count2;

        int grenadeExplodeTime;         // we've caught a grenade, which was due to explode at this time
        int grenadeFired;               // the grenade entity we last fired

        char *track;

        // entity scripting system
        char *scriptName;

        int numScriptEvents;
        g_script_event_t *scriptEvents;     // contains a list of actions to perform for each event type
        g_script_status_t scriptStatus;     // current status of scripting
        // the accumulation buffer
        int scriptAccumBuffer[10];

        float accuracy;

        char tagName[64];            // name of the tag we are attached to
        gentity_t *tagParent;
        gentity_t *tankLink;

        int lastHintCheckTime;
        int voiceChatSquelch;
        int voiceChatPreviousTime;
        int lastBurnedFrameNumber; // to fix FT instant-kill exploit

        entState_t entstate;
        char *constages;
        char *desstages;
        char *damageparent;
        int conbmodels[4];
        int desbmodels[3];
        int partofstage;

        int allowteams;

        int spawnTime;

        gentity_t *dmgparent;
        qboolean dmginloop;

        int tagNumber;              // "handle" to a tag header

        int linkTagTime;

        splinePath_t *backspline;
        vec3_t backorigin;
        float backdelta;
        qboolean back;
        qboolean moving;

        // What sort of surface are we standing on?
        int surfaceFlags;

        char tagBuffer[16];

        // bleh - ugly
        int backupWeaponTime;
        int mg42weapHeat;

        vec3_t oldOrigin;

        qboolean runthisframe;

        g_constructible_stats_t constructibleStats;

        int etpro_misc_1;

        int numPlayers;

#ifdef FEATURE_OMNIBOT
        int numPlanted; // Omni-bot increment dyno count
#endif
};

struct gclient_s {
        // ps MUST be the first element, because the server expects it
        playerState_t ps;
};
