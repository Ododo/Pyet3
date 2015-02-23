#include <boost/python.hpp>
#include <map>
#include <iostream>

#include "../include/gent.hpp"

using namespace boost;
 

#define FOFS2(m) offsetof(gentity_t, m)
#define CFOFS2(m) offsetof(gclient_t, m)

std::map<std::string, pfield_t> field_map
{

{"classname", {FOFS2(classname), F_LSTRING } },
{"model", {FOFS2(model), F_LSTRING } },
{"model2", {FOFS2(model2), F_LSTRING } },
{"message", {FOFS2(message), F_LSTRING } },
{"target", {FOFS2(target), F_LSTRING } },
{"targetname", {FOFS2(targetname), F_LSTRING } },
{"team", {FOFS2(team), F_LSTRING } },
{"aiName", {FOFS2(aiName), F_LSTRING } },
{"aiSkin", {FOFS2(aiSkin), F_LSTRING } },
{"dl_stylestring", {FOFS2(dl_stylestring), F_LSTRING } },
{"dl_shader", {FOFS2(dl_shader), F_LSTRING } },
{"spawnitem", {FOFS2(spawnitem), F_LSTRING } },
{"track", {FOFS2(track), F_LSTRING } },
{"scriptName", {FOFS2(scriptName), F_LSTRING } },
{"constages", {FOFS2(constages), F_LSTRING } },
{"desstages", {FOFS2(desstages), F_LSTRING } },
{"damageparent", {FOFS2(damageparent), F_LSTRING } },
{"tagName", {FOFS2(tagName), F_LSTRING } },


{"inuse", {FOFS2(inuse), F_INT } },
{"spawnflags", {FOFS2(spawnflags), F_INT } },
{"neverFree", {FOFS2(neverFree), F_INT } },
{"flags", {FOFS2(flags), F_INT } },
{"freetime", {FOFS2(freetime), F_INT } },
{"eventTime", {FOFS2(eventTime), F_INT } },
{"freeAfterEvent", {FOFS2(freeAfterEvent), F_INT } },
{"unlinkAfterEvent", {FOFS2(unlinkAfterEvent), F_INT } },
{"physicsObject", {FOFS2(physicsObject), F_INT } },
{"physicsBounce", {FOFS2(physicsBounce), F_INT } },
{"clipmask", {FOFS2(clipmask), F_INT } },
{"realNonSolidBModel", {FOFS2(realNonSolidBModel), F_INT } },
{"timestamp", {FOFS2(timestamp), F_INT } },
{"angle", {FOFS2(angle), F_INT } },
{"targetnamehash", {FOFS2(targetnamehash), F_INT } },
{"speed", {FOFS2(speed), F_INT } },
{"closespeed", {FOFS2(closespeed), F_INT } },
{"gDuration", {FOFS2(gDuration), F_INT } },
{"gDurationBack", {FOFS2(gDurationBack), F_INT } },
{"nextthink", {FOFS2(nextthink), F_INT } },
{"health", {FOFS2(health), F_INT } },
{"takedamage", {FOFS2(takedamage), F_INT } },
{"damage", {FOFS2(damage), F_INT } },
{"splashDamage", {FOFS2(splashDamage), F_INT } },
{"splashRadius", {FOFS2(splashRadius), F_INT } },
{"methodOfDeath", {FOFS2(methodOfDeath), F_INT } },
{"splashMethodOfDeath", {FOFS2(splashMethodOfDeath), F_INT } },
{"count", {FOFS2(count), F_INT } },
{"watertype", {FOFS2(watertype), F_INT } },
{"waterlevel", {FOFS2(waterlevel), F_INT } },
{"noise_index", {FOFS2(noise_index), F_INT } },
{"wait", {FOFS2(wait), F_INT } },
{"random", {FOFS2(random), F_INT } },
{"radius", {FOFS2(radius), F_INT } },
{"delay", {FOFS2(delay), F_INT } },
{"TargetFlag", {FOFS2(TargetFlag), F_INT } },
{"duration", {FOFS2(duration), F_INT } },
{"dl_atten", {FOFS2(dl_atten), F_INT } },
{"key", {FOFS2(key), F_INT } },
{"harc", {FOFS2(harc), F_INT } },
{"varc", {FOFS2(varc), F_INT } },
{"props_frame_state", {FOFS2(props_frame_state), F_INT } },
{"missionLevel", {FOFS2(missionLevel), F_INT } },
{"start_size", {FOFS2(start_size), F_INT } },
{"end_size", {FOFS2(end_size), F_INT } },
{"isProp", {FOFS2(isProp), F_INT } },
{"mg42BaseEnt", {FOFS2(mg42BaseEnt), F_INT } },
{"flameQuota", {FOFS2(flameQuota), F_INT } },
{"flameQuotaTime", {FOFS2(flameQuotaTime), F_INT } },
{"flameBurnEnt", {FOFS2(flameBurnEnt), F_INT } },
{"count2", {FOFS2(count2), F_INT } },
{"grenadeExplodeTime", {FOFS2(grenadeExplodeTime), F_INT } },
{"grenadeFired", {FOFS2(grenadeFired), F_INT } },
{"numScriptEvents", {FOFS2(numScriptEvents), F_INT } },
{"accuracy", {FOFS2(accuracy), F_INT } },
{"spawnTime", {FOFS2(spawnTime), F_INT } },
{"tagNumber", {FOFS2(tagNumber), F_INT } },
{"linkTagTime", {FOFS2(linkTagTime), F_INT } },
{"backdelta", {FOFS2(backdelta), F_INT } },
{"back", {FOFS2(back), F_INT } },
{"moving", {FOFS2(moving), F_INT } },
{"surfaceFlags", {FOFS2(surfaceFlags), F_INT } },
{"mg42weapHeat", {FOFS2(mg42weapHeat), F_INT } },
{"runthisframe", {FOFS2(runthisframe), F_INT } },
//{"numPlayers", {FOFS2(numPlayers), F_INT } },
{"partofstage", {FOFS2(partofstage), F_INT } },
{"deathType", {FOFS2(deathType), F_INT } },
{"r.bmodel", {FOFS2(r.bmodel), F_INT } },
{"r.contents", {FOFS2(r.contents), F_INT } },
{"r.eventTime", {FOFS2(r.eventTime), F_INT } },
{"r.linkcount", {FOFS2(r.linkcount), F_INT } },
{"r.linked", {FOFS2(r.linked), F_INT } },
{"r.ownerNum", {FOFS2(r.ownerNum), F_INT } },
{"r.singleClient", {FOFS2(r.singleClient), F_INT } },
{"r.svFlags", {FOFS2(r.svFlags), F_INT } },
{"r.worldflags", {FOFS2(r.worldflags), F_INT } },
{"s.clientNum", {FOFS2(s.clientNum), F_INT } },
{"s.constantLight", {FOFS2(s.constantLight), F_INT } },
{"s.density", {FOFS2(s.density), F_INT } },
{"s.dl_intensity", {FOFS2(s.dl_intensity), F_INT } },
{"s.dmgFlags", {FOFS2(s.dmgFlags), F_INT } },
{"s.eFlags", {FOFS2(s.eFlags), F_INT } },
{"s.eType", {FOFS2(s.eType), F_INT } },
{"s.effect1Time", {FOFS2(s.effect1Time), F_INT } },
{"s.effect3Time", {FOFS2(s.effect3Time), F_INT } },
{"s.frame", {FOFS2(s.frame), F_INT } },
{"s.groundEntityNum", {FOFS2(s.groundEntityNum), F_INT } },
{"s.loopSound", {FOFS2(s.loopSound), F_INT } },
{"s.modelindex", {FOFS2(s.modelindex), F_INT } },
{"s.modelindex2", {FOFS2(s.modelindex2), F_INT } },
{"s.number", {FOFS2(s.number), F_INT } },
{"s.onFireEnd", {FOFS2(s.onFireEnd), F_INT } },
{"s.onFireStart", {FOFS2(s.onFireStart), F_INT } },
{"s.powerups", {FOFS2(s.powerups), F_INT } },
{"s.solid", {FOFS2(s.solid), F_INT } },
{"s.teamNum", {FOFS2(s.teamNum), F_INT } },
{"s.time", {FOFS2(s.time), F_INT } },
{"s.time2", {FOFS2(s.time2), F_INT } },
{"s.weapon", {FOFS2(s.weapon), F_INT } },

{"rotate", {FOFS2(rotate), F_VECTOR } },
{"TargetAngles", {FOFS2(TargetAngles), F_VECTOR } },
{"dl_color", {FOFS2(dl_color), F_VECTOR } },
{"oldOrigin", {FOFS2(oldOrigin), F_VECTOR } },
{"s.origin", {FOFS2(s.origin), F_VECTOR } },
{"s.origin2", {FOFS2(s.origin2), F_VECTOR } },
{"r.absmax", {FOFS2(r.absmax), F_VECTOR } },
{"r.absmin", {FOFS2(r.absmin), F_VECTOR } },
{"r.currentAngles", {FOFS2(r.currentAngles), F_VECTOR } },
{"r.currentOrigin", {FOFS2(r.currentOrigin), F_VECTOR } },
{"r.maxs", {FOFS2(r.maxs), F_VECTOR } },
{"r.mins", {FOFS2(r.mins), F_VECTOR } },
{"s.angles", {FOFS2(s.angles), F_VECTOR } },
{"s.angles2", {FOFS2(s.angles2), F_VECTOR } },
{"ps.origin", {CFOFS2(ps.origin), F_VECTOR, FL_CLIENT } },
{"ps.velocity", {CFOFS2(ps.velocity), F_VECTOR, FL_CLIENT } },
{"ps.viewangles", {CFOFS2(ps.viewangles), F_VECTOR, FL_CLIENT} },
{"ps.mins", {CFOFS2(ps.mins), F_VECTOR, FL_CLIENT } },
{"ps.maxs", {CFOFS2(ps.maxs), F_VECTOR, FL_CLIENT } },


{"sess.aWeaponStats", {CFOFS2(sess.aWeaponStats), F_INTARRAY, FL_CLIENT, WS_MAX + 1 } },
{"sess.playerType", {CFOFS2(sess.playerType), F_INT, FL_CLIENT } },
{"sess.playerWeapon", {CFOFS2(sess.playerWeapon), F_INT, FL_CLIENT } },
{"sess.playerWeapon2", {CFOFS2(sess.playerWeapon2), F_INT, FL_CLIENT } },
{"sess.spawnObjectiveIndex", {CFOFS2(sess.spawnObjectiveIndex), F_INT, FL_CLIENT } },
{"sess.latchPlayerType", {CFOFS2(sess.latchPlayerType), F_INT, FL_CLIENT } },
{"sess.latchPlayerWeapon", {CFOFS2(sess.latchPlayerWeapon), F_INT, FL_CLIENT } },
{"sess.damage_given", {CFOFS2(sess.damage_given), F_INT, FL_CLIENT } },
{"sess.damage_received", {CFOFS2(sess.damage_received), F_INT, FL_CLIENT } },
{"sess.deaths", {CFOFS2(sess.deaths), F_INT, FL_CLIENT } },
{"sess.game_points", {CFOFS2(sess.game_points), F_INT, FL_CLIENT } },
{"sess.kills", {CFOFS2(sess.kills), F_INT, FL_CLIENT } },
{"sess.muted", {CFOFS2(sess.muted), F_INT, FL_CLIENT } },
{"sess.rank", {CFOFS2(sess.rank), F_INT, FL_CLIENT } },
{"sess.referee", {CFOFS2(sess.referee), F_INT, FL_CLIENT } },
{"sess.rounds", {CFOFS2(sess.rounds), F_INT, FL_CLIENT } },
{"sess.spec_invite", {CFOFS2(sess.spec_invite), F_INT, FL_CLIENT } },
{"sess.spec_team", {CFOFS2(sess.spec_team), F_INT, FL_CLIENT } },
{"sess.suicides", {CFOFS2(sess.suicides), F_INT, FL_CLIENT } },
{"sess.team_damage", {CFOFS2(sess.team_damage), F_INT, FL_CLIENT } },
{"sess.team_kills", {CFOFS2(sess.team_kills), F_INT, FL_CLIENT } },
{"sess.spectatorClient", {CFOFS2(sess.spectatorClient), F_INT, FL_CLIENT } },
{"sess.spectatorState", {CFOFS2(sess.spectatorState), F_INT, FL_CLIENT } },
{"pers.localClient", {CFOFS2(pers.localClient), F_INT, FL_CLIENT } },
{"pers.initialSpawn", {CFOFS2(pers.initialSpawn), F_INT, FL_CLIENT } },
{"pers.enterTime", {CFOFS2(pers.enterTime), F_INT, FL_CLIENT } },
{"pers.connectTime", {CFOFS2(pers.connectTime), F_INT, FL_CLIENT } },
{"pers.teamState.state", {CFOFS2(pers.teamState.state), F_INT, FL_CLIENT } },
{"pers.voteCount", {CFOFS2(pers.voteCount), F_INT, FL_CLIENT } },
{"pers.teamVoteCount", {CFOFS2(pers.teamVoteCount), F_INT, FL_CLIENT } },
{"pers.complaints", {CFOFS2(pers.complaints), F_INT, FL_CLIENT } },
{"pers.complaintClient", {CFOFS2(pers.complaintClient), F_INT, FL_CLIENT } },
{"pers.complaintEndTime", {CFOFS2(pers.complaintEndTime), F_INT, FL_CLIENT } },
{"pers.lastReinforceTime", {CFOFS2(pers.lastReinforceTime), F_INT, FL_CLIENT } },
{"pers.applicationClient", {CFOFS2(pers.applicationClient), F_INT, FL_CLIENT } },
{"pers.applicationEndTime", {CFOFS2(pers.applicationEndTime), F_INT, FL_CLIENT } },
{"pers.invitationClient", {CFOFS2(pers.invitationClient), F_INT, FL_CLIENT } },
{"pers.invitationEndTime", {CFOFS2(pers.invitationEndTime), F_INT, FL_CLIENT } },
{"pers.propositionClient", {CFOFS2(pers.propositionClient), F_INT, FL_CLIENT } },
{"pers.propositionClient2", {CFOFS2(pers.propositionClient2), F_INT, FL_CLIENT } },
{"pers.propositionEndTime", {CFOFS2(pers.propositionEndTime), F_INT, FL_CLIENT } },
{"pers.autofireteamEndTime", {CFOFS2(pers.autofireteamEndTime), F_INT, FL_CLIENT } },
{"pers.autofireteamCreateEndTime", {CFOFS2(pers.autofireteamCreateEndTime), F_INT, FL_CLIENT } },
{"pers.autofireteamJoinEndTime", {CFOFS2(pers.autofireteamJoinEndTime), F_INT, FL_CLIENT } },
{"pers.lastSpawnTime", {CFOFS2(pers.lastSpawnTime), F_INT, FL_CLIENT } },
{"pers.ready", {CFOFS2(pers.ready), F_INT, FL_CLIENT } },
{"pers.connected", {CFOFS2(pers.connected), F_INT, FL_CLIENT } },
{"pers.teamState.state", {CFOFS2(pers.teamState.state), F_INT, FL_CLIENT } },

{"ps.commandTime", {CFOFS2(ps.commandTime), F_INT, FL_CLIENT } },
{"ps.pm_type", {CFOFS2(ps.pm_type), F_INT, FL_CLIENT } },
{"ps.bobCycle", {CFOFS2(ps.bobCycle), F_INT, FL_CLIENT } },
{"ps.pm_flags", {CFOFS2(ps.pm_flags), F_INT, FL_CLIENT } },
{"ps.pm_time", {CFOFS2(ps.pm_time), F_INT, FL_CLIENT } },
{"ps.weaponTime", {CFOFS2(ps.weaponTime), F_INT, FL_CLIENT } },
{"ps.weaponDelay", {CFOFS2(ps.weaponDelay), F_INT, FL_CLIENT } },
{"ps.grenadeTimeLeft", {CFOFS2(ps.grenadeTimeLeft), F_INT, FL_CLIENT } },
{"ps.gravity", {CFOFS2(ps.gravity), F_INT, FL_CLIENT } },
{"ps.speed", {CFOFS2(ps.speed), F_INT, FL_CLIENT } },
{"ps.ping", {CFOFS2(ps.ping), F_INT, FL_CLIENT } },
{"ps.groundEntityNum", {CFOFS2(ps.groundEntityNum), F_INT, FL_CLIENT } },
{"ps.legsTimer", {CFOFS2(ps.legsTimer), F_INT, FL_CLIENT } },
{"ps.legsAnim", {CFOFS2(ps.legsAnim), F_INT, FL_CLIENT } },
{"ps.torsoTimer", {CFOFS2(ps.torsoTimer), F_INT, FL_CLIENT } },
{"ps.torsoAnim", {CFOFS2(ps.torsoAnim), F_INT, FL_CLIENT } },
{"ps.torsoTimer", {CFOFS2(ps.torsoTimer), F_INT, FL_CLIENT } },
{"ps.movementDir", {CFOFS2(ps.movementDir), F_INT, FL_CLIENT } },
{"ps.eFlags", {CFOFS2(ps.eFlags), F_INT, FL_CLIENT } },
{"ps.eventSequence", {CFOFS2(ps.eventSequence), F_INT, FL_CLIENT } },
{"ps.oldEventSequence", {CFOFS2(ps.oldEventSequence), F_INT, FL_CLIENT } },
{"ps.externalEvent", {CFOFS2(ps.externalEvent), F_INT, FL_CLIENT } },
{"ps.externalEventParm", {CFOFS2(ps.externalEventParm), F_INT, FL_CLIENT } },
{"ps.externalEventTime", {CFOFS2(ps.externalEventTime), F_INT, FL_CLIENT } },
{"ps.clientNum", {CFOFS2(ps.clientNum), F_INT, FL_CLIENT } },
{"ps.weapon", {CFOFS2(ps.weapon), F_INT, FL_CLIENT } },
{"ps.weaponstate", {CFOFS2(ps.weaponstate), F_INT, FL_CLIENT } },
{"ps.item", {CFOFS2(ps.item), F_INT, FL_CLIENT } },
{"ps.viewheight", {CFOFS2(ps.viewheight), F_INT, FL_CLIENT } },
{"ps.damageEvent", {CFOFS2(ps.damageEvent), F_INT, FL_CLIENT } },
{"ps.damageYaw", {CFOFS2(ps.damageYaw), F_INT, FL_CLIENT } },
{"ps.damageCount", {CFOFS2(ps.damageCount), F_INT, FL_CLIENT } },
{"ps.damagePitch", {CFOFS2(ps.damagePitch), F_INT, FL_CLIENT } },

{"ps.holding", {CFOFS2(ps.holding), F_INT, FL_CLIENT } },
{"ps.viewlocked", {CFOFS2(ps.viewlocked), F_INT, FL_CLIENT } },
{"ps.viewlocked_entNum", {CFOFS2(ps.viewlocked_entNum), F_INT, FL_CLIENT } },
{"ps.nextWeapon", {CFOFS2(ps.nextWeapon), F_INT, FL_CLIENT } },
{"ps.teamNum", {CFOFS2(ps.teamNum), F_INT, FL_CLIENT } },
{"ps.onFireStart", {CFOFS2(ps.onFireStart), F_INT, FL_CLIENT } },
{"ps.serverCursorHint", {CFOFS2(ps.serverCursorHint), F_INT, FL_CLIENT } },
{"ps.serverCursorHintVal", {CFOFS2(ps.serverCursorHintVal), F_INT, FL_CLIENT } },
{"ps.onFireStart", {CFOFS2(ps.onFireStart), F_INT, FL_CLIENT } },


{"ps.leanf", {CFOFS2(ps.leanf), F_FLOAT, FL_CLIENT } },
{"ps.crouchMaxZ", {CFOFS2(ps.crouchMaxZ), F_FLOAT, FL_CLIENT } },
{"ps.crouchViewHeight", {CFOFS2(ps.crouchViewHeight), F_FLOAT, FL_CLIENT } },
{"ps.standViewHeight", {CFOFS2(ps.standViewHeight), F_FLOAT, FL_CLIENT } },
{"ps.deadViewHeight", {CFOFS2(ps.deadViewHeight), F_FLOAT, FL_CLIENT } },
{"ps.runSpeedScale", {CFOFS2(ps.runSpeedScale), F_FLOAT, FL_CLIENT } },
{"ps.sprintSpeedScale", {CFOFS2(ps.sprintSpeedScale), F_FLOAT, FL_CLIENT } },
{"ps.crouchSpeedScale", {CFOFS2(ps.crouchSpeedScale), F_FLOAT, FL_CLIENT } },
{"ps.friction", {CFOFS2(ps.friction), F_FLOAT, FL_CLIENT } },


{"ps.events", {CFOFS2(ps.events), F_INTARRAY, FL_CLIENT, MAX_EVENTS } },
{"ps.eventParms", {CFOFS2(ps.eventParms), F_INTARRAY, FL_CLIENT, MAX_EVENTS } },
{"ps.stats", {CFOFS2(ps.stats), F_INTARRAY, FL_CLIENT, 16 } },
{"ps.persistant", {CFOFS2(ps.persistant), F_INTARRAY, FL_CLIENT, 16 } },
{"ps.powerups", {CFOFS2(ps.powerups), F_INTARRAY, FL_CLIENT, 16 } },
{"ps.ammo", {CFOFS2(ps.ammo), F_INTARRAY, FL_CLIENT, 64 } },
{"ps.ammoclip", {CFOFS2(ps.ammoclip), F_INTARRAY, FL_CLIENT, 64 } },
{"ps.holdable", {CFOFS2(ps.holdable), F_INTARRAY, FL_CLIENT, 16 } },
{"ps.weapons", {CFOFS2(ps.weapons), F_INTARRAY, FL_CLIENT, MAX_WEAPONS / ( sizeof( int ) * 8 ) } },
{"ps.delta_angles", {CFOFS2(ps.delta_angles), F_INTARRAY, FL_CLIENT, 3 } },

{"target_ent", {FOFS2(target_ent), F_ENTITY}},
{"nextTrain", {FOFS2(nextTrain), F_ENTITY}},
{"prevTrain", {FOFS2(prevTrain), F_ENTITY}},
{"chain", {FOFS2(chain), F_ENTITY}},
{"enemy", {FOFS2(enemy), F_ENTITY}},
{"activator", {FOFS2(activator), F_ENTITY}},
{"teamchain", {FOFS2(teamchain), F_ENTITY}},
{"teammaster", {FOFS2(teammaster), F_ENTITY}},
{"tagParent", {FOFS2(tagParent), F_ENTITY}},
{"tankLink", {FOFS2(tankLink), F_ENTITY}}
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
