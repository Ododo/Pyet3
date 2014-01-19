#include <boost/python.hpp>
#include <map>
#include "../include/gent_parser.hpp"


using namespace boost;


std::map<std::string, pfield_t> field_map
{

{"classname", {FOFS(classname), F_LSTRING } },
{"model", {FOFS(model), F_LSTRING } },
{"model2", {FOFS(model2), F_LSTRING } },
{"message", {FOFS(message), F_LSTRING } },
{"target", {FOFS(target), F_LSTRING } },
{"targetname", {FOFS(targetname), F_LSTRING } },
{"team", {FOFS(team), F_LSTRING } },
{"aiName", {FOFS(aiName), F_LSTRING } },
{"aiSkin", {FOFS(aiSkin), F_LSTRING } },
{"dl_stylestring", {FOFS(dl_stylestring), F_LSTRING } },
{"dl_shader", {FOFS(dl_shader), F_LSTRING } },
{"spawnitem", {FOFS(spawnitem), F_LSTRING } },
{"track", {FOFS(track), F_LSTRING } },
{"scriptName", {FOFS(scriptName), F_LSTRING } },
{"constages", {FOFS(constages), F_LSTRING } },
{"desstages", {FOFS(desstages), F_LSTRING } },
{"damageparent", {FOFS(damageparent), F_LSTRING } },
{"tagName", {FOFS(tagName), F_LSTRING } },


{"inuse", {FOFS(inuse), F_INT } },
{"spawnflags", {FOFS(spawnflags), F_INT } },
{"neverFree", {FOFS(neverFree), F_INT } },
{"flags", {FOFS(flags), F_INT } },
{"freetime", {FOFS(freetime), F_INT } },
{"eventTime", {FOFS(eventTime), F_INT } },
{"freeAfterEvent", {FOFS(freeAfterEvent), F_INT } },
{"unlinkAfterEvent", {FOFS(unlinkAfterEvent), F_INT } },
{"physicsObject", {FOFS(physicsObject), F_INT } },
{"physicsBounce", {FOFS(physicsBounce), F_INT } },
{"clipmask", {FOFS(clipmask), F_INT } },
{"realNonSolidBModel", {FOFS(realNonSolidBModel), F_INT } },
{"timestamp", {FOFS(timestamp), F_INT } },
{"angle", {FOFS(angle), F_INT } },
{"targetnamehash", {FOFS(targetnamehash), F_INT } },
{"speed", {FOFS(speed), F_INT } },
{"closespeed", {FOFS(closespeed), F_INT } },
{"gDuration", {FOFS(gDuration), F_INT } },
{"gDurationBack", {FOFS(gDurationBack), F_INT } },
{"nextthink", {FOFS(nextthink), F_INT } },
{"health", {FOFS(health), F_INT } },
{"takedamage", {FOFS(takedamage), F_INT } },
{"damage", {FOFS(damage), F_INT } },
{"splashDamage", {FOFS(splashDamage), F_INT } },
{"splashRadius", {FOFS(splashRadius), F_INT } },
{"methodOfDeath", {FOFS(methodOfDeath), F_INT } },
{"splashMethodOfDeath", {FOFS(splashMethodOfDeath), F_INT } },
{"count", {FOFS(count), F_INT } },
{"watertype", {FOFS(watertype), F_INT } },
{"waterlevel", {FOFS(waterlevel), F_INT } },
{"noise_index", {FOFS(noise_index), F_INT } },
{"wait", {FOFS(wait), F_INT } },
{"random", {FOFS(random), F_INT } },
{"radius", {FOFS(radius), F_INT } },
{"delay", {FOFS(delay), F_INT } },
{"TargetFlag", {FOFS(TargetFlag), F_INT } },
{"duration", {FOFS(duration), F_INT } },
{"dl_atten", {FOFS(dl_atten), F_INT } },
{"key", {FOFS(key), F_INT } },
{"harc", {FOFS(harc), F_INT } },
{"varc", {FOFS(varc), F_INT } },
{"props_frame_state", {FOFS(props_frame_state), F_INT } },
{"missionLevel", {FOFS(missionLevel), F_INT } },
{"start_size", {FOFS(start_size), F_INT } },
{"end_size", {FOFS(end_size), F_INT } },
{"isProp", {FOFS(isProp), F_INT } },
{"mg42BaseEnt", {FOFS(mg42BaseEnt), F_INT } },
{"flameQuota", {FOFS(flameQuota), F_INT } },
{"flameQuotaTime", {FOFS(flameQuotaTime), F_INT } },
{"flameBurnEnt", {FOFS(flameBurnEnt), F_INT } },
{"count2", {FOFS(count2), F_INT } },
{"grenadeExplodeTime", {FOFS(grenadeExplodeTime), F_INT } },
{"grenadeFired", {FOFS(grenadeFired), F_INT } },
{"numScriptEvents", {FOFS(numScriptEvents), F_INT } },
{"accuracy", {FOFS(accuracy), F_INT } },
{"spawnTime", {FOFS(spawnTime), F_INT } },
{"tagNumber", {FOFS(tagNumber), F_INT } },
{"linkTagTime", {FOFS(linkTagTime), F_INT } },
{"backdelta", {FOFS(backdelta), F_INT } },
{"back", {FOFS(back), F_INT } },
{"moving", {FOFS(moving), F_INT } },
{"surfaceFlags", {FOFS(surfaceFlags), F_INT } },
{"mg42weapHeat", {FOFS(mg42weapHeat), F_INT } },
{"runthisframe", {FOFS(runthisframe), F_INT } },
{"numPlayers", {FOFS(numPlayers), F_INT } },
{"partofstage", {FOFS(partofstage), F_INT } },
{"deathType", {FOFS(deathType), F_INT } },
{"r.bmodel", {FOFS(r.bmodel), F_INT } },
{"r.contents", {FOFS(r.contents), F_INT } },
{"r.eventTime", {FOFS(r.eventTime), F_INT } },
{"r.linkcount", {FOFS(r.linkcount), F_INT } },
{"r.linked", {FOFS(r.linked), F_INT } },
{"r.ownerNum", {FOFS(r.ownerNum), F_INT } },
{"r.singleClient", {FOFS(r.singleClient), F_INT } },
{"r.svFlags", {FOFS(r.svFlags), F_INT } },
{"r.worldflags", {FOFS(r.worldflags), F_INT } },
{"s.clientNum", {FOFS(s.clientNum), F_INT } },
{"s.constantLight", {FOFS(s.constantLight), F_INT } },
{"s.density", {FOFS(s.density), F_INT } },
{"s.dl_intensity", {FOFS(s.dl_intensity), F_INT } },
{"s.dmgFlags", {FOFS(s.dmgFlags), F_INT } },
{"s.eFlags", {FOFS(s.eFlags), F_INT } },
{"s.eType", {FOFS(s.eType), F_INT } },
{"s.effect1Time", {FOFS(s.effect1Time), F_INT } },
{"s.effect3Time", {FOFS(s.effect3Time), F_INT } },
{"s.frame", {FOFS(s.frame), F_INT } },
{"s.groundEntityNum", {FOFS(s.groundEntityNum), F_INT } },
{"s.loopSound", {FOFS(s.loopSound), F_INT } },
{"s.modelindex", {FOFS(s.modelindex), F_INT } },
{"s.modelindex2", {FOFS(s.modelindex2), F_INT } },
{"s.number", {FOFS(s.number), F_INT } },
{"s.onFireEnd", {FOFS(s.onFireEnd), F_INT } },
{"s.onFireStart", {FOFS(s.onFireStart), F_INT } },
{"s.powerups", {FOFS(s.powerups), F_INT } },
{"s.solid", {FOFS(s.solid), F_INT } },
{"s.teamNum", {FOFS(s.teamNum), F_INT } },
{"s.time", {FOFS(s.time), F_INT } },
{"s.time2", {FOFS(s.time2), F_INT } },
{"s.weapon", {FOFS(s.weapon), F_INT } },

{"rotate", {FOFS(rotate), F_VECTOR } },
{"TargetAngles", {FOFS(TargetAngles), F_VECTOR } },
{"dl_color", {FOFS(dl_color), F_VECTOR } },
{"oldOrigin", {FOFS(oldOrigin), F_VECTOR } },
{"s.origin", {FOFS(s.origin), F_VECTOR } },
{"s.origin2", {FOFS(s.origin2), F_VECTOR } },
{"r.absmax", {FOFS(r.absmax), F_VECTOR } },
{"r.absmin", {FOFS(r.absmin), F_VECTOR } },
{"r.currentAngles", {FOFS(r.currentAngles), F_VECTOR } },
{"r.currentOrigin", {FOFS(r.currentOrigin), F_VECTOR } },
{"r.maxs", {FOFS(r.maxs), F_VECTOR } },
{"r.mins", {FOFS(r.mins), F_VECTOR } },
{"s.angles", {FOFS(s.angles), F_VECTOR } },
{"s.angles2", {FOFS(s.angles2), F_VECTOR } },


{"sess.aWeaponStats", {CLIENTOFS(sess.aWeaponStats), F_INTARRAY, FL_CLIENT, WS_MAX + 1 } },
{"sess.playerType", {CLIENTOFS(sess.playerType), F_INT, FL_CLIENT } },
{"sess.playerWeapon", {CLIENTOFS(sess.playerWeapon), F_INT, FL_CLIENT } },
{"sess.playerWeapon2", {CLIENTOFS(sess.playerWeapon2), F_INT, FL_CLIENT } },
{"sess.spawnObjectiveIndex", {CLIENTOFS(sess.spawnObjectiveIndex), F_INT, FL_CLIENT } },
{"sess.latchPlayerType", {CLIENTOFS(sess.latchPlayerType), F_INT, FL_CLIENT } },
{"sess.latchPlayerWeapon", {CLIENTOFS(sess.latchPlayerWeapon), F_INT, FL_CLIENT } },
{"sess.damage_given", {CLIENTOFS(sess.damage_given), F_INT, FL_CLIENT } },
{"sess.damage_received", {CLIENTOFS(sess.damage_received), F_INT, FL_CLIENT } },
{"sess.deaths", {CLIENTOFS(sess.deaths), F_INT, FL_CLIENT } },
{"sess.game_points", {CLIENTOFS(sess.game_points), F_INT, FL_CLIENT } },
{"sess.kills", {CLIENTOFS(sess.kills), F_INT, FL_CLIENT } },
{"sess.muted", {CLIENTOFS(sess.muted), F_INT, FL_CLIENT } },
{"sess.rank", {CLIENTOFS(sess.rank), F_INT, FL_CLIENT } },
{"sess.referee", {CLIENTOFS(sess.referee), F_INT, FL_CLIENT } },
{"sess.rounds", {CLIENTOFS(sess.rounds), F_INT, FL_CLIENT } },
{"sess.spec_invite", {CLIENTOFS(sess.spec_invite), F_INT, FL_CLIENT } },
{"sess.spec_team", {CLIENTOFS(sess.spec_team), F_INT, FL_CLIENT } },
{"sess.suicides", {CLIENTOFS(sess.suicides), F_INT, FL_CLIENT } },
{"sess.team_damage", {CLIENTOFS(sess.team_damage), F_INT, FL_CLIENT } },
{"sess.team_kills", {CLIENTOFS(sess.team_kills), F_INT, FL_CLIENT } },
{"sess.spectatorClient", {CLIENTOFS(sess.spectatorClient), F_INT, FL_CLIENT } },
{"sess.spectatorState", {CLIENTOFS(sess.spectatorState), F_INT, FL_CLIENT } },
{"pers.localClient", {CLIENTOFS(pers.localClient), F_INT, FL_CLIENT } },
{"pers.initialSpawn", {CLIENTOFS(pers.initialSpawn), F_INT, FL_CLIENT } },
{"pers.enterTime", {CLIENTOFS(pers.enterTime), F_INT, FL_CLIENT } },
{"pers.connectTime", {CLIENTOFS(pers.connectTime), F_INT, FL_CLIENT } },
{"pers.teamState.state", {CLIENTOFS(pers.teamState.state), F_INT, FL_CLIENT } },
{"pers.voteCount", {CLIENTOFS(pers.voteCount), F_INT, FL_CLIENT } },
{"pers.teamVoteCount", {CLIENTOFS(pers.teamVoteCount), F_INT, FL_CLIENT } },
{"pers.complaints", {CLIENTOFS(pers.complaints), F_INT, FL_CLIENT } },
{"pers.complaintClient", {CLIENTOFS(pers.complaintClient), F_INT, FL_CLIENT } },
{"pers.complaintEndTime", {CLIENTOFS(pers.complaintEndTime), F_INT, FL_CLIENT } },
{"pers.lastReinforceTime", {CLIENTOFS(pers.lastReinforceTime), F_INT, FL_CLIENT } },
{"pers.applicationClient", {CLIENTOFS(pers.applicationClient), F_INT, FL_CLIENT } },
{"pers.applicationEndTime", {CLIENTOFS(pers.applicationEndTime), F_INT, FL_CLIENT } },
{"pers.invitationClient", {CLIENTOFS(pers.invitationClient), F_INT, FL_CLIENT } },
{"pers.invitationEndTime", {CLIENTOFS(pers.invitationEndTime), F_INT, FL_CLIENT } },
{"pers.propositionClient", {CLIENTOFS(pers.propositionClient), F_INT, FL_CLIENT } },
{"pers.propositionClient2", {CLIENTOFS(pers.propositionClient2), F_INT, FL_CLIENT } },
{"pers.propositionEndTime", {CLIENTOFS(pers.propositionEndTime), F_INT, FL_CLIENT } },
{"pers.autofireteamEndTime", {CLIENTOFS(pers.autofireteamEndTime), F_INT, FL_CLIENT } },
{"pers.autofireteamCreateEndTime", {CLIENTOFS(pers.autofireteamCreateEndTime	), F_INT, FL_CLIENT } },
{"pers.autofireteamJoinEndTime", {CLIENTOFS(pers.autofireteamJoinEndTime), F_INT, FL_CLIENT } },
{"pers.lastSpawnTime", {CLIENTOFS(pers.lastSpawnTime), F_INT, FL_CLIENT } },
{"pers.ready", {CLIENTOFS(pers.ready), F_INT, FL_CLIENT } },
{"pers.connected", {CLIENTOFS(pers.connected), F_INT, FL_CLIENT } },
{"pers.teamState.state", {CLIENTOFS(pers.teamState.state), F_INT, FL_CLIENT } },
{"ps.ping", {CLIENTOFS(ps.ping), F_INT, FL_CLIENT } },
{"ps.stats", {CLIENTOFS(ps.stats), F_INTARRAY, FL_CLIENT, 16 } },
{"ps.persistant", {CLIENTOFS(ps.persistant), F_INTARRAY, FL_CLIENT, 16 } },
{"ps.powerups", {CLIENTOFS(ps.powerups), F_INTARRAY, FL_CLIENT, 16 } },
{"ps.ammo", {CLIENTOFS(ps.ammo), F_INTARRAY, FL_CLIENT, 64 } },
{"ps.ammoclip", {CLIENTOFS(ps.ammoclip), F_INTARRAY, FL_CLIENT, 64 } },

{"target_ent", {FOFS(target_ent), F_ENTITY}},

{"nextTrain", {FOFS(nextTrain), F_ENTITY}},
{"prevTrain", {FOFS(prevTrain), F_ENTITY}},
{"chain", {FOFS(chain), F_ENTITY}},
{"enemy", {FOFS(enemy), F_ENTITY}},
{"activator", {FOFS(activator), F_ENTITY}},
{"teamchain", {FOFS(teamchain), F_ENTITY}},
{"teammaster", {FOFS(teammaster), F_ENTITY}},
{"tagParent", {FOFS(tagParent), F_ENTITY}},
{"tankLink", {FOFS(tankLink), F_ENTITY}}
};


python::object
GetValueForString(gentity_t* entities, gentity_t *e, std::string field){

    python::list list;
    python::object obj;
    pfield_t fld = field_map[field];
    byte * ent;
    gentity_t * target;

    switch(fld.flags){
        case FL_NONE:
            ent = (byte *)e;
            break;
        case FL_CLIENT:
            if(!e->client){
                std::cout << "[PYET] - Client reserved field requested for non-client entity" << std::endl;
                return python::object();
            }
            ent = (byte *)e->client;
            break;
    }
    //looks like lua api code but i don't see any other way to do it
    try{

    switch(fld.type){

        case F_LSTRING:
        case F_GSTRING:
            obj = python::object(std::string(GetAttrByOfs(char*, ent, fld.ofs)));
            return obj;

        case F_INT:
            obj = python::object(GetAttrByOfs(int, ent, fld.ofs));
            return obj;

        case F_FLOAT:
            obj = python::object(GetAttrByOfs(float, ent, fld.ofs));
            return obj;

        case F_VECTOR:
            ArrayToList(3, GetAttrByOfs(vec3_t, ent, fld.ofs), list);
            return list;

        case F_INTARRAY:
            typedef int t[fld.array_size];
            ArrayToList(fld.array_size, GetAttrByOfs(t, ent, fld.ofs),list);
            return list;

        case F_ENTITY:
            target = GetAttrByOfs(gentity_t *, ent, fld.ofs);
            if (target){
                obj = python::object(target - entities);
            }
            return obj;

        default:
            return python::object();
    }

    } //end try
    catch(...){
        // boost::python::handle_exception();
         return python::object();
    }
    return python::object();

}

int SetValueForString(gentity_t *e, std::string field, python::object value){
    pfield_t fld = field_map[field];
    python::list list;
    byte * ent;

    switch(fld.flags){

        case FL_NONE:
            ent = (byte *)e;
            break;

        case FL_CLIENT:
            if(!e->client) return 0;
            ent = (byte *)e->client;
            break;
    }

    try{
    switch(fld.type){

        case F_LSTRING:
        case F_GSTRING:
            GetAttrByOfs(char*, ent, fld.ofs) =  python::extract<char *>(value);
            return 1;

        case F_INT:
            GetAttrByOfs(int, ent, fld.ofs) =  python::extract<int>(value);
            return 1;

        case F_FLOAT:
            GetAttrByOfs(float, ent, fld.ofs) = python::extract<float>(value);
            return 1;

        case F_VECTOR:
            list = python::extract<python::list>(value);
            ListToArray(3, GetAttrByOfs(vec3_t, ent, fld.ofs), list);
            return 1;

        case F_INTARRAY:
            list = python::extract<python::list>(value);
            if (python::len(list) <= fld.array_size){
                typedef int t[fld.array_size];
                ListToArray(fld.array_size, GetAttrByOfs(t, ent, fld.ofs), list);
                return 1;
            }

        case F_ENTITY:
        default:
            return 0;
    }

    }
    catch(...){
        boost::python::handle_exception();
       // std::cout << "[PYET] - Bad value type for field : " <<  field << std::endl;
    }

    return 0;
}
