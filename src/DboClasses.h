/*
*    Copyright (C) 2012 Siof, lukaasm <lukaasm.pl>
*
*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU Affero General Public License version 3 as
*    published by the Free Software Foundation.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU Affero General Public License for more details.
*
*    You should have received a copy of the GNU Affero General Public License
*    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef H_dboClasses
#define H_dboClasses

#include <string>

#include <Wt/Dbo/Dbo>

namespace Wt
{
    class WContainerWidget;
    class WString;
    class WTableCell;
    class WText;
}

enum Searchers
{
    SEARCH_NONE         = -1,
    SEARCH_CREATURE     = 0,
    SEARCH_GAMEOBJECT   = 1,
    SEARCH_QUEST        = 2,
    SEARCH_SPELL        = 3,
    SEARCH_ITEM         = 4,

    SEARCH_MAX
};

static const char * SearcherTableNames[] =
{
    "creature_template",
    "gameobject_template",
    "quest_template",
    "spell_template",
    "item_template"
};

static const char * SearcherInternalPaths[] =
{
    "npc",
    "object",
    "quest",
    "spell",
    "item"
};

class TemplateInfo
{
    public:
        TemplateInfo() : _entry(0), _name("") {}
        TemplateInfo(long entry, std::string & name) : _entry(entry), _name(name) {}
        TemplateInfo(const long & entry, const std::string & name) : _entry(entry), _name(name) {}

        virtual Wt::WContainerWidget * CreateContainer() const { return NULL; }

        const long & GetEntry() const { return _entry; }
        const std::string & GetName() const { return _name; }

        template<class T>
        std::string GetAsString(T & value) const;

        template<class Action>
        void persist(Action& a)
        {
            Wt::Dbo::id(a, _entry, "entry");
            Wt::Dbo::field(a, _name, "name");
        }

    protected:
        Wt::WText * addWText(Wt::WContainerWidget * cont, Wt::WString text) const;
        Wt::WText * addWText(Wt::WTableCell * cont, Wt::WString text) const;

        long _entry;
        std::string _name;
};

typedef Wt::Dbo::collection<Wt::Dbo::ptr<TemplateInfo> > SearchResults;

class CreatureTemplateInfo : protected TemplateInfo
{
    public:
        CreatureTemplateInfo();
        CreatureTemplateInfo(const CreatureTemplateInfo & cti);

        template<class Action>
        void persist(Action& a)
        {
            TemplateInfo::persist(a);

            Wt::Dbo::field(a, _heroicEntry, "heroic_entry");
            Wt::Dbo::field(a, _killCredit, "KillCredit");
            Wt::Dbo::field(a, _modelIdA[0], "modelid_A");
            Wt::Dbo::field(a, _modelIdA[1], "modelid_A2");
            Wt::Dbo::field(a, _modelIdH[0], "modelid_H");
            Wt::Dbo::field(a, _modelIdH[1], "modelid_H2");
            Wt::Dbo::field(a, _subName, "subname");
            Wt::Dbo::field(a, _iconName, "IconName");
            Wt::Dbo::field(a, _minLevel, "minlevel");
            Wt::Dbo::field(a, _maxLevel, "maxlevel");
            Wt::Dbo::field(a, _minHealth, "minhealth");
            Wt::Dbo::field(a, _maxHealth, "maxhealth");
            Wt::Dbo::field(a, _minMana, "minmana");
            Wt::Dbo::field(a, _maxMana, "maxmana");
            Wt::Dbo::field(a, _armor, "armor");
            Wt::Dbo::field(a, _factionA, "faction_A");
            Wt::Dbo::field(a, _factionH, "faction_H");
            Wt::Dbo::field(a, _npcFlags, "npcflag");
            Wt::Dbo::field(a, _speed, "speed");
            Wt::Dbo::field(a, _scale, "scale");
            Wt::Dbo::field(a, _rank, "rank");
            Wt::Dbo::field(a, _minDmg, "mindmg");
            Wt::Dbo::field(a, _maxDmg, "maxdmg");
            Wt::Dbo::field(a, _dmgSchool, "dmgschool");
            Wt::Dbo::field(a, _attackPower, "attackpower");
            Wt::Dbo::field(a, _baseAttackTime, "baseattacktime");
            Wt::Dbo::field(a, _rangeAttackTime, "rangeattacktime");
            Wt::Dbo::field(a, _unitFlags, "unit_flags");
            Wt::Dbo::field(a, _dynamicFlags, "dynamicflags");
            Wt::Dbo::field(a, _family, "family");
            Wt::Dbo::field(a, _trainerType, "trainer_type");
            Wt::Dbo::field(a, _trainerSpell, "trainer_spell");
            Wt::Dbo::field(a, _class, "class");
            Wt::Dbo::field(a, _race, "race");
            Wt::Dbo::field(a, _minRangeDmg, "minrangedmg");
            Wt::Dbo::field(a, _maxRangeDmg, "maxrangedmg");
            Wt::Dbo::field(a, _rangeAttackPower, "rangedattackpower");
            Wt::Dbo::field(a, _type, "type");
            Wt::Dbo::field(a, _typeFlags, "type_flags");
            Wt::Dbo::field(a, _lootId, "lootid");
            Wt::Dbo::field(a, _pickPocketLoot, "pickpocketloot");
            Wt::Dbo::field(a, _skinLoot, "skinloot");
            Wt::Dbo::field(a, _resistance[0], "resistance1");
            Wt::Dbo::field(a, _resistance[1], "resistance2");
            Wt::Dbo::field(a, _resistance[2], "resistance3");
            Wt::Dbo::field(a, _resistance[3], "resistance4");
            Wt::Dbo::field(a, _resistance[4], "resistance5");
            Wt::Dbo::field(a, _resistance[5], "resistance6");
            Wt::Dbo::field(a, _spell[0], "spell1");
            Wt::Dbo::field(a, _spell[1], "spell2");
            Wt::Dbo::field(a, _spell[2], "spell3");
            Wt::Dbo::field(a, _spell[3], "spell4");
            Wt::Dbo::field(a, _spell[4], "spell5");
            Wt::Dbo::field(a, _petSpellDataId, "PetSpellDataId");
            Wt::Dbo::field(a, _minGold, "mingold");
            Wt::Dbo::field(a, _maxGold, "maxgold");
            Wt::Dbo::field(a, _aiName, "AIName");
            Wt::Dbo::field(a, _movementType, "MovementType");
            Wt::Dbo::field(a, _inhabitType, "InhabitType");
            Wt::Dbo::field(a, _racialLeader, "RacialLeader");
            Wt::Dbo::field(a, _regenHealth, "RegenHealth");
            Wt::Dbo::field(a, _equipmentId, "equipment_id");
            Wt::Dbo::field(a, _mechanicImmuneMask, "mechanic_immune_mask");
            Wt::Dbo::field(a, _flagsExtra, "flags_extra");
            Wt::Dbo::field(a, _scriptName, "ScriptName");
        }

        virtual Wt::WContainerWidget * CreateContainer() const;

        const long & GetHeroicEntry() const { return _heroicEntry; }
        const long & GetKillCredit() const { return _killCredit; }
        const long & GetModelIdA(unsigned int i) const { return _modelIdA[i]; }
        const long & GetModelIdH(unsigned int i) const { return _modelIdH[i]; }
        const std::string & GetSubName() const { return _subName; }
        const std::string & GetIconName() const { return _iconName; }
        const int & GetMinLevel() const { return _minLevel; }
        const int & GetMaxLevel() const { return _maxLevel; }
        const double & GetMinHealth() const { return _minHealth; }
        const double & GetMaxHealth() const { return _maxHealth; }
        const double & GetMinMana() const { return _minMana; }
        const double & GetMaxMana() const { return _maxMana; }
        const long & GetArmor() const { return _armor; }
        const int & GetFactionA() const { return _factionA; }
        const int & GetFactionH() const { return _factionH; }
        const double & GetNpcFlags() const { return _npcFlags; }
        const float & GetSpeed() const { return _speed; }
        const float & GetScale() const { return _scale; }
        const int & GetRank() const { return _rank; }
        const float & GetMinDmg() const { return _minDmg; }
        const float & GetMaxDmg() const { return _maxDmg; }
        const int & GetDmgSchool() const { return _dmgSchool; }
        const double & GetAttackPower() const { return _attackPower; }
        const double & GetBaseAttackTime() const { return _baseAttackTime; }
        const double & GetRangeAttackTime() const { return _rangeAttackTime; }
        const double & GetUnitFlags() const { return _unitFlags; }
        const double & GetDynamicFlags() const { return _dynamicFlags; }
        const int & GetFamily() const { return _family; }
        const int & GetTrainerType() const { return _trainerType; }
        const int & GetTrainerSpell() const { return _trainerSpell; }
        const int & GetClass() const { return _class; }
        const int & GetRace() const { return _race; }
        const float & GetMinRangeDmg() const { return _minRangeDmg; }
        const float & GetMaxRangeDmg() const { return _maxRangeDmg; }
        const long & GetRangeAttackPower() const { return _rangeAttackPower; }
        const int & GetType() const { return _type; }
        const double & GetTypeFlags() const { return _typeFlags; }
        const int & GetLootId() const { return _lootId; }
        const int & GetPickPocketLoot() const { return _pickPocketLoot; }
        const int & GetSkinLoot() const { return _skinLoot; }
        const int & GetResistance(unsigned int i) const { return _resistance[i]; }
        const int & GetSpell(unsigned int i) const { return _spell[i]; }
        const int & GetPetSpellDataId() const { return _petSpellDataId; }
        const long & GetMinGold() const { return _minGold; }
        const long & GetMaxGold() const { return _maxGold; }
        const std::string & GetAiName() const { return _aiName; }
        const int & GetMovementType() const { return _movementType; }
        const int & GetInhabitType() const { return _inhabitType; }
        const int & GetRacialLeader() const { return _racialLeader; }
        const int & GetRegenHealth() const { return _regenHealth; }
        const int & GetEquipmentId() const { return _equipmentId; }
        const double & GetMechanicImmuneMask() const { return _mechanicImmuneMask; }
        const double & GetFlagsExtra() const { return _flagsExtra; }
        const std::string & GetScriptName() const { return _scriptName; }

    private:
        long _heroicEntry;
        long _killCredit;
        long _modelIdA[2];
        long _modelIdH[2];
        std::string _subName;
        std::string _iconName;
        int _minLevel;
        int _maxLevel;
        double _minHealth;
        double _maxHealth;
        double _minMana;
        double _maxMana;
        long _armor;
        int _factionA;
        int _factionH;
        double _npcFlags;
        float _speed;
        float _scale;
        int _rank;
        float _minDmg;
        float _maxDmg;
        int _dmgSchool;
        double _attackPower;
        double _baseAttackTime;
        double _rangeAttackTime;
        double _unitFlags;
        double _dynamicFlags;
        int _family;
        int _trainerType;
        int _trainerSpell;
        int _class;
        int _race;
        float _minRangeDmg;
        float _maxRangeDmg;
        long _rangeAttackPower;
        int _type;
        double _typeFlags;
        int _lootId;
        int _pickPocketLoot;
        int _skinLoot;
        int _resistance[6];
        int _spell[5];
        int _petSpellDataId;
        long _minGold;
        long _maxGold;
        std::string _aiName;
        int _movementType;
        int _inhabitType;
        int _racialLeader;
        int _regenHealth;
        int _equipmentId;
        double _mechanicImmuneMask;
        double _flagsExtra;
        std::string _scriptName;
};

class GameObjectTemplateInfo : protected TemplateInfo
{
    public:
        GameObjectTemplateInfo();
        GameObjectTemplateInfo(const GameObjectTemplateInfo & gti);

        template<class Action>
        void persist(Action& a)
        {
            TemplateInfo::persist(a);

            Wt::Dbo::field(a, _type, "type");
            Wt::Dbo::field(a, _displayId, "displayId");
            Wt::Dbo::field(a, _castBarCaption, "castBarCaption");
            Wt::Dbo::field(a, _faction, "faction");
            Wt::Dbo::field(a, _flags, "flags");
            Wt::Dbo::field(a, _size, "size");
            Wt::Dbo::field(a, _data[0], "data0");
            Wt::Dbo::field(a, _data[1], "data1");
            Wt::Dbo::field(a, _data[2], "data2");
            Wt::Dbo::field(a, _data[3], "data3");
            Wt::Dbo::field(a, _data[4], "data4");
            Wt::Dbo::field(a, _data[5], "data5");
            Wt::Dbo::field(a, _data[6], "data6");
            Wt::Dbo::field(a, _data[7], "data7");
            Wt::Dbo::field(a, _data[8], "data8");
            Wt::Dbo::field(a, _data[9], "data9");
            Wt::Dbo::field(a, _data[10], "data10");
            Wt::Dbo::field(a, _data[11], "data11");
            Wt::Dbo::field(a, _data[12], "data12");
            Wt::Dbo::field(a, _data[13], "data13");
            Wt::Dbo::field(a, _data[14], "data14");
            Wt::Dbo::field(a, _data[15], "data15");
            Wt::Dbo::field(a, _data[16], "data16");
            Wt::Dbo::field(a, _data[17], "data17");
            Wt::Dbo::field(a, _data[18], "data18");
            Wt::Dbo::field(a, _data[19], "data19");
            Wt::Dbo::field(a, _data[10], "data20");
            Wt::Dbo::field(a, _data[21], "data21");
            Wt::Dbo::field(a, _data[22], "data22");
            Wt::Dbo::field(a, _data[23], "data23");
            Wt::Dbo::field(a, _scriptName, "ScriptName");
        }

        virtual Wt::WContainerWidget * CreateContainer() const;

        const int & GetType() const { return _type; }
        const int & GetDisplayId() const { return _displayId; }
        const std::string & GetCastBarCaption() const { return _castBarCaption; }
        const int & GetFaction() const { return _faction; }
        const long & GetFlags() const { return _flags; }
        const float & GetSize() const { return _size; }
        const int & GetData(unsigned int i) const { return _data[i]; }
        const std::string & GetScriptName() const { return _scriptName; }

    private:
        int _type;
        int _displayId;
        std::string _castBarCaption;
        int _faction;
        long _flags;
        float _size;
        int _data[24];
        std::string _scriptName;
};

class QuestTemplateInfo : protected TemplateInfo
{
    public:
        QuestTemplateInfo();
        QuestTemplateInfo(const QuestTemplateInfo & qti);

        template<class Action>
        void persist(Action& a)
        {
            TemplateInfo::persist(a);

            Wt::Dbo::field(a, _method, "Method");
            Wt::Dbo::field(a, _zoneOrSort, "ZoneOrSort");
            Wt::Dbo::field(a, _skillOrClass, "SkillOrClass");
            Wt::Dbo::field(a, _minLevel, "MinLevel");
            Wt::Dbo::field(a, _questLevel, "QuestLevel");
            Wt::Dbo::field(a, _type, "Type");
            Wt::Dbo::field(a, _requiredRaces, "RequiredRaces");
            Wt::Dbo::field(a, _requiredSkillValue, "RequiredSkillValue");
            Wt::Dbo::field(a, _repObjectiveFaction, "RepObjectiveFaction");
            Wt::Dbo::field(a, _repObjectiveValue, "RepObjectiveValue");
            Wt::Dbo::field(a, _requiredMinRepFaction, "RequiredMinRepFaction");
            Wt::Dbo::field(a, _requiredMinRepValue, "RequiredMinRepValue");
            Wt::Dbo::field(a, _requiredMaxRepFaction, "RequiredMaxRepFaction");
            Wt::Dbo::field(a, _requiredMaxRepValue, "RequiredMaxRepValue");
            Wt::Dbo::field(a, _suggestedPlayers, "SuggestedPlayers");
            Wt::Dbo::field(a, _limitTime, "LimitTime");
            Wt::Dbo::field(a, _questFlags, "QuestFlags");
            Wt::Dbo::field(a, _specialFlags, "SpecialFlags");
            Wt::Dbo::field(a, _charTitleId, "CharTitleId");
            Wt::Dbo::field(a, _prevQuestId, "PrevQuestId");
            Wt::Dbo::field(a, _nextQuestId, "NextQuestId");
            Wt::Dbo::field(a, _exclusiveGroup, "ExclusiveGroup");
            Wt::Dbo::field(a, _nextQuestInChain, "NextQuestInChain");
            Wt::Dbo::field(a, _srcItemId, "SrcItemId");
            Wt::Dbo::field(a, _srcItemCount, "SrcItemCount");
            Wt::Dbo::field(a, _srcSpell, "SrcSpell");
            Wt::Dbo::field(a, _details, "Details");
            Wt::Dbo::field(a, _objectives, "Objectives");
            Wt::Dbo::field(a, _offerRewardText, "OfferRewardText");
            Wt::Dbo::field(a, _requestItemsText, "RequestItemsText");
            Wt::Dbo::field(a, _endText, "EndText");
            Wt::Dbo::field(a, _objectiveText[0], "ObjectiveText1");
            Wt::Dbo::field(a, _objectiveText[1], "ObjectiveText2");
            Wt::Dbo::field(a, _objectiveText[2], "ObjectiveText3");
            Wt::Dbo::field(a, _objectiveText[3], "ObjectiveText4");
            Wt::Dbo::field(a, _reqItemId[0], "ReqItemId1");
            Wt::Dbo::field(a, _reqItemId[1], "ReqItemId2");
            Wt::Dbo::field(a, _reqItemId[2], "ReqItemId3");
            Wt::Dbo::field(a, _reqItemId[3], "ReqItemId4");
            Wt::Dbo::field(a, _reqItemCount[0], "ReqItemCount1");
            Wt::Dbo::field(a, _reqItemCount[1], "ReqItemCount2");
            Wt::Dbo::field(a, _reqItemCount[2], "ReqItemCount3");
            Wt::Dbo::field(a, _reqItemCount[3], "ReqItemCount4");
            Wt::Dbo::field(a, _reqSourceId[0], "ReqSourceId1");
            Wt::Dbo::field(a, _reqSourceId[1], "ReqSourceId2");
            Wt::Dbo::field(a, _reqSourceId[2], "ReqSourceId3");
            Wt::Dbo::field(a, _reqSourceId[3], "ReqSourceId4");
            Wt::Dbo::field(a, _reqSourceCount[0], "ReqSourceCount1");
            Wt::Dbo::field(a, _reqSourceCount[1], "ReqSourceCount2");
            Wt::Dbo::field(a, _reqSourceCount[2], "ReqSourceCount3");
            Wt::Dbo::field(a, _reqSourceCount[3], "ReqSourceCount4");
            Wt::Dbo::field(a, _reqSourceRef[0], "ReqSourceRef1");
            Wt::Dbo::field(a, _reqSourceRef[1], "ReqSourceRef2");
            Wt::Dbo::field(a, _reqSourceRef[2], "ReqSourceRef3");
            Wt::Dbo::field(a, _reqSourceRef[3], "ReqSourceRef4");
            Wt::Dbo::field(a, _reqCreatureOrGOId[0], "ReqCreatureOrGOId1");
            Wt::Dbo::field(a, _reqCreatureOrGOId[1], "ReqCreatureOrGOId2");
            Wt::Dbo::field(a, _reqCreatureOrGOId[2], "ReqCreatureOrGOId3");
            Wt::Dbo::field(a, _reqCreatureOrGOId[3], "ReqCreatureOrGOId4");
            Wt::Dbo::field(a, _reqCreatureOrGOCount[0], "ReqCreatureOrGOCount1");
            Wt::Dbo::field(a, _reqCreatureOrGOCount[1], "ReqCreatureOrGOCount2");
            Wt::Dbo::field(a, _reqCreatureOrGOCount[2], "ReqCreatureOrGOCount3");
            Wt::Dbo::field(a, _reqCreatureOrGOCount[3], "ReqCreatureOrGOCount4");
            Wt::Dbo::field(a, _reqSpellCast[0], "ReqSpellCast1");
            Wt::Dbo::field(a, _reqSpellCast[1], "ReqSpellCast2");
            Wt::Dbo::field(a, _reqSpellCast[2], "ReqSpellCast3");
            Wt::Dbo::field(a, _reqSpellCast[3], "ReqSpellCast4");
            Wt::Dbo::field(a, _rewChoiceItemId[0], "RewChoiceItemId1");
            Wt::Dbo::field(a, _rewChoiceItemId[1], "RewChoiceItemId2");
            Wt::Dbo::field(a, _rewChoiceItemId[2], "RewChoiceItemId3");
            Wt::Dbo::field(a, _rewChoiceItemId[3], "RewChoiceItemId4");
            Wt::Dbo::field(a, _rewChoiceItemId[4], "RewChoiceItemId5");
            Wt::Dbo::field(a, _rewChoiceItemId[5], "RewChoiceItemId6");
            Wt::Dbo::field(a, _rewChoiceItemCount[0], "RewChoiceItemCount1");
            Wt::Dbo::field(a, _rewChoiceItemCount[1], "RewChoiceItemCount2");
            Wt::Dbo::field(a, _rewChoiceItemCount[2], "RewChoiceItemCount3");
            Wt::Dbo::field(a, _rewChoiceItemCount[3], "RewChoiceItemCount4");
            Wt::Dbo::field(a, _rewChoiceItemCount[4], "RewChoiceItemCount5");
            Wt::Dbo::field(a, _rewChoiceItemCount[5], "RewChoiceItemCount6");
            Wt::Dbo::field(a, _rewItemId[0], "RewItemId1");
            Wt::Dbo::field(a, _rewItemId[1], "RewItemId2");
            Wt::Dbo::field(a, _rewItemId[2], "RewItemId3");
            Wt::Dbo::field(a, _rewItemId[3], "RewItemId4");
            Wt::Dbo::field(a, _rewItemCount[0], "RewItemCount1");
            Wt::Dbo::field(a, _rewItemCount[1], "RewItemCount2");
            Wt::Dbo::field(a, _rewItemCount[2], "RewItemCount3");
            Wt::Dbo::field(a, _rewItemCount[3], "RewItemCount4");
            Wt::Dbo::field(a, _rewRepFaction[0], "RewRepFaction1");
            Wt::Dbo::field(a, _rewRepFaction[1], "RewRepFaction2");
            Wt::Dbo::field(a, _rewRepFaction[2], "RewRepFaction3");
            Wt::Dbo::field(a, _rewRepFaction[3], "RewRepFaction4");
            Wt::Dbo::field(a, _rewRepFaction[4], "RewRepFaction5");
            Wt::Dbo::field(a, _rewRepValue[0], "RewRepValue1");
            Wt::Dbo::field(a, _rewRepValue[1], "RewRepValue2");
            Wt::Dbo::field(a, _rewRepValue[2], "RewRepValue3");
            Wt::Dbo::field(a, _rewRepValue[3], "RewRepValue4");
            Wt::Dbo::field(a, _rewRepValue[4], "RewRepValue5");
            Wt::Dbo::field(a, _rewHonorableKills, "RewHonorableKills");
            Wt::Dbo::field(a, _rewOrReqMoney, "RewOrReqMoney");
            Wt::Dbo::field(a, _rewMoneyMaxLevel, "RewMoneyMaxLevel");
            Wt::Dbo::field(a, _rewSpell, "RewSpell");
            Wt::Dbo::field(a, _rewSpellCast, "RewSpellCast");
            Wt::Dbo::field(a, _rewMailTemplateId, "RewMailTemplateId");
            Wt::Dbo::field(a, _rewMailDelaySecs, "RewMailDelaySecs");
            Wt::Dbo::field(a, _pointMapId, "PointMapId");
            Wt::Dbo::field(a, _pointX, "PointX");
            Wt::Dbo::field(a, _pointY, "PointY");
            Wt::Dbo::field(a, _pointOpt, "PointOpt");
            Wt::Dbo::field(a, _detailsEmote[0], "DetailsEmote1");
            Wt::Dbo::field(a, _detailsEmote[1], "DetailsEmote2");
            Wt::Dbo::field(a, _detailsEmote[2], "DetailsEmote3");
            Wt::Dbo::field(a, _detailsEmote[3], "DetailsEmote4");
            Wt::Dbo::field(a, _incompleteEmote, "IncompleteEmote");
            Wt::Dbo::field(a, _completeEmote, "CompleteEmote");
            Wt::Dbo::field(a, _offerRewardEmote[0], "OfferRewardEmote1");
            Wt::Dbo::field(a, _offerRewardEmote[1], "OfferRewardEmote2");
            Wt::Dbo::field(a, _offerRewardEmote[2], "OfferRewardEmote3");
            Wt::Dbo::field(a, _offerRewardEmote[3], "OfferRewardEmote4");
            Wt::Dbo::field(a, _startScript, "StartScript");
            Wt::Dbo::field(a, _completeScript, "CompleteScript");
        }

        virtual Wt::WContainerWidget * CreateContainer() const;

        const int & GetMethod() const { return _method; }
        const int & GetZoneOrSort() const { return _zoneOrSort; }
        const int & GetSkillOrClass() const { return _skillOrClass; }
        const int & GetMinLevel() const { return _minLevel; }
        const int & GetQuestLevel() const { return _questLevel; }
        const int & GetType() const { return _type; }
        const int & GetRequiredRaces() const { return _requiredRaces; }
        const int & GetRequiredSkillValue() const { return _requiredSkillValue; }
        const int & GetRepObjectiveFaction() const { return _repObjectiveFaction; }
        const int & GetRepObjectiveValue() const { return _repObjectiveValue; }
        const int & GetRequiredMinRepFaction() const { return _requiredMinRepFaction; }
        const int & GetRequiredMinRepValue() const { return _requiredMinRepValue; }
        const int & GetRequiredMaxRepFaction() const { return _requiredMaxRepFaction; }
        const int & GetRequiredMaxRepValue() const { return _requiredMaxRepValue; }
        const int & GetSuggestedPlayers() const { return _suggestedPlayers; }
        const long & GetLimitTime() const { return _limitTime; }
        const long & GetQuestFlags() const { return _questFlags; }
        const long & GetSpecialFlags() const { return _specialFlags; }
        const int & GetCharTitleId() const { return _charTitleId; }
        const int & GetPrevQuestId() const { return _prevQuestId; }
        const int & GetNextQuestId() const { return _nextQuestId; }
        const int & GetExclusiveGroup() const { return _exclusiveGroup; }
        const int & GetNextQuestInChain() const { return _nextQuestInChain; }
        const int & GetSrcItemId() const { return _srcItemId; }
        const int & GetSrcItemCount() const { return _srcItemCount; }
        const int & GetSrcSpell() const { return _srcSpell; }
        const std::string & GetDetails() const { return _details; }
        const std::string & GetObjectives() const { return _objectives; }
        const std::string & GetOfferRewardText() const { return _offerRewardText; }
        const std::string & GetRequestItemsText() const { return _requestItemsText; }
        const std::string & GetEndText() const { return _endText; }
        const std::string & GetObjectiveText(unsigned int i) const { return _objectiveText[i]; }
        const int & GetReqItemId(unsigned int i) const { return _reqItemId[i]; }
        const int & GetReqItemCount(unsigned int i) const { return _reqItemCount[i]; }
        const int & GetReqSourceId(unsigned int i) const { return _reqSourceId[i]; }
        const int & GetReqSourceCount(unsigned int i) const { return _reqSourceCount[i]; }
        const int & GetReqSourceRef(unsigned int i) const { return _reqSourceRef[i]; }
        const int & GetReqCreatureOrGOId(unsigned int i) const { return _reqCreatureOrGOId[i]; }
        const int & GetReqCreatureOrGOCount(unsigned int i) const { return _reqCreatureOrGOCount[i]; }
        const int & GetReqSpellCast(unsigned int i) const { return _reqSpellCast[i]; }
        const int & GetRewChoiceItemId(unsigned int i) const { return _rewChoiceItemId[i]; }
        const int & GetRewChoiceItemCount(unsigned int i) const { return _rewChoiceItemCount[i]; }
        const int & GetRewItemId(unsigned int i) const { return _rewItemId[i]; }
        const int & GetRewItemCount(unsigned int i) const { return _rewItemCount[i]; }
        const int & GetRewRepFaction(unsigned int i) const { return _rewRepFaction[i]; }
        const int & GetRewRepValue(unsigned int i) const { return _rewRepValue[i]; }
        const int & GetRewHonorableKills() const { return _rewHonorableKills; }
        const long & GetRewOrReqMoney() const { return _rewOrReqMoney; }
        const long & GetRewMoneyMaxLevel() const { return _rewMoneyMaxLevel; }
        const int & GetRewSpell() const { return _rewSpell; }
        const int & GetRewSpellCast() const { return _rewSpellCast; }
        const int & GetRewMailTemplateId() const { return _rewMailTemplateId; }
        const long & GetRewMailDelaySecs() const { return _rewMailDelaySecs; }
        const int & GetPointMapId() const { return _pointMapId; }
        const float & GetPointX() const { return _pointX; }
        const float & GetPointY() const { return _pointY; }
        const int & GetPointOpt() const { return _pointOpt; }
        const int & GetDetailsEmote(unsigned int i) const { return _detailsEmote[0]; }
        const int & GetIncompleteEmote() const { return _incompleteEmote; }
        const int & GetCompleteEmote() const { return _completeEmote; }
        const int & GetOfferRewardEmote(unsigned int i) const { return _offerRewardEmote[i]; }
        const int & GetStartScript() const { return _startScript; }
        const int & GetCompleteScript() const { return _completeScript; }

    private:
        int _method;
        int _zoneOrSort;
        int _skillOrClass;
        int _minLevel;
        int _questLevel;
        int _type;
        int _requiredRaces;
        int _requiredSkillValue;
        int _repObjectiveFaction;
        int _repObjectiveValue;
        int _requiredMinRepFaction;
        int _requiredMinRepValue;
        int _requiredMaxRepFaction;
        int _requiredMaxRepValue;
        int _suggestedPlayers;
        long _limitTime;
        long _questFlags;
        long _specialFlags;
        int _charTitleId;
        int _prevQuestId;
        int _nextQuestId;
        int _exclusiveGroup;
        int _nextQuestInChain;
        int _srcItemId;
        int _srcItemCount;
        int _srcSpell;
        std::string _details;
        std::string _objectives;
        std::string _offerRewardText;
        std::string _requestItemsText;
        std::string _endText;
        std::string _objectiveText[4];
        int _reqItemId[4];
        int _reqItemCount[4];
        int _reqSourceId[4];
        int _reqSourceCount[4];
        int _reqSourceRef[4];
        int _reqCreatureOrGOId[4];
        int _reqCreatureOrGOCount[4];
        int _reqSpellCast[4];
        int _rewChoiceItemId[6];
        int _rewChoiceItemCount[6];
        int _rewItemId[4];
        int _rewItemCount[4];
        int _rewRepFaction[5];
        int _rewRepValue[5];
        int _rewHonorableKills;
        long _rewOrReqMoney;
        long _rewMoneyMaxLevel;
        int _rewSpell;
        int _rewSpellCast;
        int _rewMailTemplateId;
        long _rewMailDelaySecs;
        int _pointMapId;
        float _pointX;
        float _pointY;
        int _pointOpt;
        int _detailsEmote[4];
        int _incompleteEmote;
        int _completeEmote;
        int _offerRewardEmote[4];
        int _startScript;
        int _completeScript;
};

class SpellTemplateInfo : protected TemplateInfo
{
    public:
        SpellTemplateInfo();
        SpellTemplateInfo(const SpellTemplateInfo & sti);

        template<class Action>
        void persist(Action& a)
        {
            TemplateInfo::persist(a);

            Wt::Dbo::field(a, _category, "category");
            Wt::Dbo::field(a, _castUI, "castUI");
            Wt::Dbo::field(a, _dispel, "dispel");
            Wt::Dbo::field(a, _mechanic, "mechanic");
            Wt::Dbo::field(a, _attributes, "attributes");
            Wt::Dbo::field(a, _attributesEx[0], "attributesEx");
            Wt::Dbo::field(a, _attributesEx[1], "attributesEx2");
            Wt::Dbo::field(a, _attributesEx[2], "attributesEx3");
            Wt::Dbo::field(a, _attributesEx[3], "attributesEx4");
            Wt::Dbo::field(a, _attributesEx[4], "attributesEx5");
            Wt::Dbo::field(a, _attributesEx[5], "attributesEx6");
            Wt::Dbo::field(a, _stances, "stances");
            Wt::Dbo::field(a, _stancesNot, "stancesNot");
            Wt::Dbo::field(a, _targets, "targets");
            Wt::Dbo::field(a, _targetCreatureType, "targetCreatureType");
            Wt::Dbo::field(a, _requiresSpellFocus, "requiresSpellFocus");
            Wt::Dbo::field(a, _facingCasterFlags, "facingCasterFlags");
            Wt::Dbo::field(a, _casterAuraState, "casterAuraState");
            Wt::Dbo::field(a, _targetAuraState, "targetAuraState");
            Wt::Dbo::field(a, _casterAuraStateNot, "casterAuraStateNot");
            Wt::Dbo::field(a, _targetAuraStateNot, "targetAuraStateNot");
            Wt::Dbo::field(a, _castingTimeIndex, "castingTimeIndex");
            Wt::Dbo::field(a, _recoveryTime, "recoveryTime");
            Wt::Dbo::field(a, _categoryRecoveryTime, "categoryRecoveryTime");
            Wt::Dbo::field(a, _interruptFlags, "interruptFlags");
            Wt::Dbo::field(a, _auraInterruptFlags, "auraInterruptFlags");
            Wt::Dbo::field(a, _channelInterruptFlags, "channelInterruptFlags");
            Wt::Dbo::field(a, _procFlags, "procFlags");
            Wt::Dbo::field(a, _procChance, "procChance");
            Wt::Dbo::field(a, _procCharges, "procCharges");
            Wt::Dbo::field(a, _maxLevel, "maxLevel");
            Wt::Dbo::field(a, _baseLevel, "baseLevel");
            Wt::Dbo::field(a, _spellLevel, "spellLevel");
            Wt::Dbo::field(a, _durationIndex, "durationIndex");
            Wt::Dbo::field(a, _powerType, "powerType");
            Wt::Dbo::field(a, _manaCost, "manaCost");
            Wt::Dbo::field(a, _manaCostPerLevel, "manaCostPerLevel");
            Wt::Dbo::field(a, _manaPerSecond, "manaPerSecond");
            Wt::Dbo::field(a, _manaPerSecondPerLevel, "manaPerSecondPerLevel");
            Wt::Dbo::field(a, _rangeIndex, "rangeIndex");
            Wt::Dbo::field(a, _speed, "speed");
            Wt::Dbo::field(a, _modalNextSpell, "modalNextSpell");
            Wt::Dbo::field(a, _stackAmount, "stackAmount");
            Wt::Dbo::field(a, _totem[0], "totem1");
            Wt::Dbo::field(a, _totem[1], "totem2");
            Wt::Dbo::field(a, _reagent[0], "reagent1");
            Wt::Dbo::field(a, _reagent[1], "reagent2");
            Wt::Dbo::field(a, _reagent[2], "reagent3");
            Wt::Dbo::field(a, _reagent[3], "reagent4");
            Wt::Dbo::field(a, _reagent[4], "reagent5");
            Wt::Dbo::field(a, _reagent[5], "reagent6");
            Wt::Dbo::field(a, _reagent[6], "reagent7");
            Wt::Dbo::field(a, _reagent[7], "reagent8");
            Wt::Dbo::field(a, _reagentCount[0], "reagentCount1");
            Wt::Dbo::field(a, _reagentCount[1], "reagentCount2");
            Wt::Dbo::field(a, _reagentCount[2], "reagentCount3");
            Wt::Dbo::field(a, _reagentCount[3], "reagentCount4");
            Wt::Dbo::field(a, _reagentCount[4], "reagentCount5");
            Wt::Dbo::field(a, _reagentCount[5], "reagentCount6");
            Wt::Dbo::field(a, _reagentCount[6], "reagentCount7");
            Wt::Dbo::field(a, _reagentCount[7], "reagentCount8");
            Wt::Dbo::field(a, _equippedItemClass, "equippedItemClass");
            Wt::Dbo::field(a, _equippedItemSubClassMask, "equippedItemSubClassMask");
            Wt::Dbo::field(a, _equippedItemInventoryTypeMask, "equippedItemInventoryTypeMask");
            Wt::Dbo::field(a, _effect[0], "effect1");
            Wt::Dbo::field(a, _effect[1], "effect2");
            Wt::Dbo::field(a, _effect[2], "effect3");
            Wt::Dbo::field(a, _effectDieSides[0], "effectDieSides1");
            Wt::Dbo::field(a, _effectDieSides[1], "effectDieSides2");
            Wt::Dbo::field(a, _effectDieSides[2], "effectDieSides3");
            Wt::Dbo::field(a, _effectBaseDice[0], "effectBaseDice1");
            Wt::Dbo::field(a, _effectBaseDice[1], "effectBaseDice2");
            Wt::Dbo::field(a, _effectBaseDice[2], "effectBaseDice3");
            Wt::Dbo::field(a, _effectDicePerLevel[0], "effectDicePerLevel1");
            Wt::Dbo::field(a, _effectDicePerLevel[1], "effectDicePerLevel2");
            Wt::Dbo::field(a, _effectDicePerLevel[2], "effectDicePerLevel3");
            Wt::Dbo::field(a, _effectRealPointsPerLevel[0], "effectRealPointsPerLevel1");
            Wt::Dbo::field(a, _effectRealPointsPerLevel[1], "effectRealPointsPerLevel2");
            Wt::Dbo::field(a, _effectRealPointsPerLevel[2], "effectRealPointsPerLevel3");
            Wt::Dbo::field(a, _effectBasePoints[0], "effectBasePoints1");
            Wt::Dbo::field(a, _effectBasePoints[1], "effectBasePoints2");
            Wt::Dbo::field(a, _effectBasePoints[2], "effectBasePoints3");
            Wt::Dbo::field(a, _effectMechanic[0], "effectMechanic1");
            Wt::Dbo::field(a, _effectMechanic[1], "effectMechanic2");
            Wt::Dbo::field(a, _effectMechanic[2], "effectMechanic3");
            Wt::Dbo::field(a, _effectImplicitTargetA[0], "effectImplicitTargetA1");
            Wt::Dbo::field(a, _effectImplicitTargetA[1], "effectImplicitTargetA2");
            Wt::Dbo::field(a, _effectImplicitTargetA[2], "effectImplicitTargetA3");
            Wt::Dbo::field(a, _effectImplicitTargetB[0], "effectImplicitTargetB1");
            Wt::Dbo::field(a, _effectImplicitTargetB[1], "effectImplicitTargetB2");
            Wt::Dbo::field(a, _effectImplicitTargetB[2], "effectImplicitTargetB3");
            Wt::Dbo::field(a, _effectRadiusIndex[0], "effectRadiusIndex1");
            Wt::Dbo::field(a, _effectRadiusIndex[1], "effectRadiusIndex2");
            Wt::Dbo::field(a, _effectRadiusIndex[2], "effectRadiusIndex3");
            Wt::Dbo::field(a, _effectApplyAuraName[0], "effectApplyAuraName1");
            Wt::Dbo::field(a, _effectApplyAuraName[1], "effectApplyAuraName2");
            Wt::Dbo::field(a, _effectApplyAuraName[2], "effectApplyAuraName3");
            Wt::Dbo::field(a, _effectAmplitude[0], "effectAmplitude1");
            Wt::Dbo::field(a, _effectAmplitude[1], "effectAmplitude2");
            Wt::Dbo::field(a, _effectAmplitude[2], "effectAmplitude3");
            Wt::Dbo::field(a, _effectMultipleValue[0], "effectMultipleValue1");
            Wt::Dbo::field(a, _effectMultipleValue[1], "effectMultipleValue2");
            Wt::Dbo::field(a, _effectMultipleValue[2], "effectMultipleValue3");
            Wt::Dbo::field(a, _effectChainTarget[0], "effectChainTarget1");
            Wt::Dbo::field(a, _effectChainTarget[1], "effectChainTarget2");
            Wt::Dbo::field(a, _effectChainTarget[2], "effectChainTarget3");
            Wt::Dbo::field(a, _effectItemType[0], "effectItemType1");
            Wt::Dbo::field(a, _effectItemType[1], "effectItemType2");
            Wt::Dbo::field(a, _effectItemType[2], "effectItemType3");
            Wt::Dbo::field(a, _effectMiscValue[0], "effectMiscValue1");
            Wt::Dbo::field(a, _effectMiscValue[1], "effectMiscValue2");
            Wt::Dbo::field(a, _effectMiscValue[2], "effectMiscValue3");
            Wt::Dbo::field(a, _effectMiscValueB[0], "effectMiscValueB1");
            Wt::Dbo::field(a, _effectMiscValueB[1], "effectMiscValueB2");
            Wt::Dbo::field(a, _effectMiscValueB[2], "effectMiscValueB3");
            Wt::Dbo::field(a, _effectTriggerSpell[0], "effectTriggerSpell1");
            Wt::Dbo::field(a, _effectTriggerSpell[1], "effectTriggerSpell2");
            Wt::Dbo::field(a, _effectTriggerSpell[2], "effectTriggerSpell3");
            Wt::Dbo::field(a, _effectPointsPerComboPoint[0], "effectPointsPerComboPoint1");
            Wt::Dbo::field(a, _effectPointsPerComboPoint[1], "effectPointsPerComboPoint2");
            Wt::Dbo::field(a, _effectPointsPerComboPoint[2], "effectPointsPerComboPoint3");
            Wt::Dbo::field(a, _spellVisual, "spellVisual");
            Wt::Dbo::field(a, _unknown1, "unknown1");
            Wt::Dbo::field(a, _spellIconID, "spellIconID");
            Wt::Dbo::field(a, _activeIconID, "activeIconID");
            Wt::Dbo::field(a, _spellPriority, "spellPriority");
            Wt::Dbo::field(a, _nameFlag, "nameFlag");
            Wt::Dbo::field(a, _rank, "rank");
            Wt::Dbo::field(a, _rankFlags, "rankFlags");
            Wt::Dbo::field(a, _description, "description");
            Wt::Dbo::field(a, _descriptionFlags, "descriptionFlags");
            Wt::Dbo::field(a, _toolTip, "toolTip");
            Wt::Dbo::field(a, _toolTipFlags, "toolTipFlags");
            Wt::Dbo::field(a, _manaCostPercentage, "manaCostPercentage");
            Wt::Dbo::field(a, _startRecoveryCategory, "startRecoveryCategory");
            Wt::Dbo::field(a, _startRecoveryTime, "startRecoveryTime");
            Wt::Dbo::field(a, _maxTargetLevel, "maxTargetLevel");
            Wt::Dbo::field(a, _spellFamilyName, "spellFamilyName");
            Wt::Dbo::field(a, _spellFamilyFlags, "spellFamilyFlags");
            Wt::Dbo::field(a, _spellFamilyFlags2, "spellFamilyFlags2");
            Wt::Dbo::field(a, _maxAffectedTargets, "maxAffectedTargets");
            Wt::Dbo::field(a, _dmgClass, "dmgClass");
            Wt::Dbo::field(a, _preventionType, "preventionType");
            Wt::Dbo::field(a, _stanceBarOrder, "stanceBarOrder");
            Wt::Dbo::field(a, _dmgMultiplier[0], "dmgMultiplier1");
            Wt::Dbo::field(a, _dmgMultiplier[1], "dmgMultiplier2");
            Wt::Dbo::field(a, _dmgMultiplier[2], "dmgMultiplier3");
            Wt::Dbo::field(a, _attributesCu, "attributesCu");
            Wt::Dbo::field(a, _minReputation, "minReputation");
            Wt::Dbo::field(a, _requiredAuraVision, "requiredAuraVision");
            Wt::Dbo::field(a, _totemCategory[0], "totemCategory1");
            Wt::Dbo::field(a, _totemCategory[1], "totemCategory2");
            Wt::Dbo::field(a, _areaId, "areaId");
            Wt::Dbo::field(a, _schoolMask, "schoolMask");
        }

        virtual Wt::WContainerWidget * CreateContainer() const;

        const long & GetCategory() const { return _category; }
        const long & GetCastUI() const { return _castUI; }
        const long & GetDispel() const { return _dispel; }
        const long & GetMechanic() const { return _mechanic; }
        const long & GetAttributes() const { return _attributes; }
        const long & GetAttributesEx(unsigned int i) const { return _attributesEx[i]; }
        const long & GetStances() const { return _stances; }
        const long & GetStancesNot() const { return _stancesNot; }
        const long & GetTargets() const { return _targets; }
        const long & GetTargetCreatureType() const { return _targetCreatureType; }
        const long & GetRequiresSpellFocus() const { return _requiresSpellFocus; }
        const long & GetFacingCasterFlags() const { return _facingCasterFlags; }
        const long & GetCasterAuraState() const { return _casterAuraState; }
        const long & GetTargetAuraState() const { return _targetAuraState; }
        const long & GetCasterAuraStateNot() const { return _casterAuraStateNot; }
        const long & GetTargetAuraStateNot() const { return _targetAuraStateNot; }
        const long & GetCastingTimeIndex() const { return _castingTimeIndex; }
        const long & GetRecoveryTime() const { return _recoveryTime; }
        const long & GetCategoryRecoveryTime() const { return _categoryRecoveryTime; }
        const long & GetInterruptFlags() const { return _interruptFlags; }
        const long & GetAuraInterruptFlags() const { return _auraInterruptFlags; }
        const long & GetChannelInterruptFlags() const { return _channelInterruptFlags; }
        const long & GetProcFlags() const { return _procFlags; }
        const long & GetProcChance() const { return _procChance; }
        const long & GetProcCharges() const { return _procCharges; }
        const long & GetMaxLevel() const { return _maxLevel; }
        const long & GetBaseLevel() const { return _baseLevel; }
        const long & GetSpellLevel() const { return _spellLevel; }
        const long & GetDurationIndex() const { return _durationIndex; }
        const long & GetPowerType() const { return _powerType; }
        const long & GetManaCost() const { return _manaCost; }
        const long & GetManaCostPerLevel() const { return _manaCostPerLevel; }
        const long & GetManaPerSecond() const { return _manaPerSecond; }
        const long & GetManaPerSecondPerLevel() const { return _manaCostPerLevel; }
        const long & GetRangeIndex() const { return _rangeIndex; }
        const float & GetSpeed() const { return _speed; }
        const long & GetModalNextSpell() const { return _modalNextSpell; }
        const long & GetStackAmount() const { return _stackAmount; }
        const long & GetTotem(unsigned int i) const { return _totem[i]; }
        const int & GetReagent(unsigned int i) const { return _reagent[i]; }
        const long & GetReagentCount(unsigned int i) const { return _reagentCount[i]; }
        const int & GetEquippedItemClass() const { return _equippedItemClass; }
        const int & GetEquippedItemSubClassMask() const { return _equippedItemSubClassMask; }
        const int & GetEquippedItemInventoryTypeMask() const { return _equippedItemInventoryTypeMask; }
        const long & GetEffect(unsigned int i) const { return _effect[i]; }
        const int & GetEffectDieSides(unsigned int i) const { return _effectDieSides[i]; }
        const long & GetEffectBaseDice(unsigned int i) const { return _effectBaseDice[i]; }
        const float & GetEffectDicePerLevel(unsigned int i) const { return _effectDicePerLevel[i]; }
        const float & GetEffectRealPointsPerLevel(unsigned int i) const { return _effectRealPointsPerLevel[i]; }
        const int & GetEffectBasePoints(unsigned int i) const { return _effectBasePoints[i]; }
        const long & GetEffectMechanic(unsigned int i) const { return _effectMechanic[i]; }
        const long & GetEffectImplicitTargetA(unsigned int i) const { return _effectImplicitTargetA[i]; }
        const long & GetEffectImplicitTargetB(unsigned int i) const { return _effectImplicitTargetB[i]; }
        const long & GetEffectRadiusIndex(unsigned int i) const { return _effectRadiusIndex[i]; }
        const long & GetEffectApplyAuraName(unsigned int i) const { return _effectApplyAuraName[i]; }
        const long & GetEffectAmplitude(unsigned int i) const { return _effectAmplitude[i]; }
        const float & GetEffectMultipleValue(unsigned int i) const { return _effectMultipleValue[i]; }
        const long & GetEffectChainTarget(unsigned int i) const { return _effectChainTarget[i]; }
        const long & GetEffectItemType(unsigned int i) const { return _effectItemType[i]; }
        const int & GetEffectMiscValue(unsigned int i) const { return _effectMiscValue[i]; }
        const int & GetEffectMiscValueB(unsigned int i) const { return _effectMiscValueB[i]; }
        const long & GetEffectTriggerSpell(unsigned int i) const { return _effectTriggerSpell[i]; }
        const float & GetEffectPointsPerComboPoint(unsigned int i) const { return _effectPointsPerComboPoint[i]; }
        const long & GetSpellVisual() const { return _spellVisual; }
        const long & GetUnknown1() const { return _unknown1; }
        const long & GetSpellIconID() const { return _spellIconID; }
        const long & GetActiveIconID() const { return _activeIconID; }
        const long & GetSpellPriority() const { return _spellPriority; }
        const long & GetNameFlag() const { return _nameFlag; }
        const std::string & GetRank() const { return _rank; }
        const long & GetRankFlags() const { return _rankFlags; }
        const std::string & GetDescription() const { return _description; }
        const long & GetDescriptionFlags() const { return _descriptionFlags; }
        const std::string & GetToolTip() const { return _toolTip; }
        const long & GetToolTipFlags() const { return _toolTipFlags; }
        const long & GetManaCostPercentage() const { return _manaCostPercentage; }
        const long & GetStartRecoveryCategory() const { return _startRecoveryCategory; }
        const long & GetStartRecoveryTime() const { return _startRecoveryTime; }
        const long & GetMaxTargetLevel() const { return _maxTargetLevel; }
        const long & GetSpellFamilyName() const { return _spellFamilyName; }
        long long GetSpellFamilyFlags() const { return _spellFamilyFlags + (_spellFamilyFlags2 << 32); }    // guessed
        const long & GetSpellFamilyFlags1() const { return _spellFamilyFlags; }
        const long & GetSpellFamilyFlags2() const { return _spellFamilyFlags2; }
        const long & GetMaxAffectedTargets() const { return _maxAffectedTargets; }
        const long & GetDmgClass() const { return _dmgClass; }
        const long & GetPreventionType() const { return _preventionType; }
        const long & GetStanceBarOrder() const { return _stanceBarOrder; }
        const float & GetDmgMultiplier(unsigned int i) const { return _dmgMultiplier[i]; }
        const long & GetAttributesCu() const { return _attributesCu; }
        const long & GetMinReputation() const { return _minReputation; }
        const long & GetRequiredAuraVision() const { return _requiredAuraVision; }
        const long & GetTotemCategory(unsigned int i) const { return _totemCategory[i]; }
        const long & GetAreaId() const { return _areaId; }
        const long & GetSchoolMask() const { return _schoolMask; }

    private:
        long _category;
        long _castUI;
        long _dispel;
        long _mechanic;
        long _attributes;
        long _attributesEx[6];
        long _stances;
        long _stancesNot;
        long _targets;
        long _targetCreatureType;
        long _requiresSpellFocus;
        long _facingCasterFlags;
        long _casterAuraState;
        long _targetAuraState;
        long _casterAuraStateNot;
        long _targetAuraStateNot;
        long _castingTimeIndex;
        long _recoveryTime;
        long _categoryRecoveryTime;
        long _interruptFlags;
        long _auraInterruptFlags;
        long _channelInterruptFlags;
        long _procFlags;
        long _procChance;
        long _procCharges;
        long _maxLevel;
        long _baseLevel;
        long _spellLevel;
        long _durationIndex;
        long _powerType;
        long _manaCost;
        long _manaCostPerLevel;
        long _manaPerSecond;
        long _manaPerSecondPerLevel;
        long _rangeIndex;
        float _speed;
        long _modalNextSpell;
        long _stackAmount;
        long _totem[2];
        int _reagent[8];
        long _reagentCount[8];
        int _equippedItemClass;
        int _equippedItemSubClassMask;
        int _equippedItemInventoryTypeMask;
        long _effect[3];
        int _effectDieSides[3];
        long _effectBaseDice[3];
        float _effectDicePerLevel[3];
        float _effectRealPointsPerLevel[3];
        int _effectBasePoints[3];
        long _effectMechanic[3];
        long _effectImplicitTargetA[3];
        long _effectImplicitTargetB[3];
        long _effectRadiusIndex[3];
        long _effectApplyAuraName[3];
        long _effectAmplitude[3];
        float _effectMultipleValue[3];
        long _effectChainTarget[3];
        long _effectItemType[3];
        int _effectMiscValue[3];
        int _effectMiscValueB[3];
        long _effectTriggerSpell[3];
        float _effectPointsPerComboPoint[3];
        long _spellVisual;
        long _unknown1;
        long _spellIconID;
        long _activeIconID;
        long _spellPriority;
        //std::string _name[16];
        long _nameFlag;
        std::string _rank;//[16];
        long _rankFlags;
        std::string _description;//[16];
        long _descriptionFlags;
        std::string _toolTip;//[16];
        long _toolTipFlags;
        long _manaCostPercentage;
        long _startRecoveryCategory;
        long _startRecoveryTime;
        long _maxTargetLevel;
        long _spellFamilyName;
        long _spellFamilyFlags;
        long _spellFamilyFlags2;
        long _maxAffectedTargets;
        long _dmgClass;
        long _preventionType;
        long _stanceBarOrder;
        float _dmgMultiplier[3];
        long _attributesCu;
        long _minReputation;
        long _requiredAuraVision;
        long _totemCategory[2];
        long _areaId;
        long _schoolMask;
};

class ItemTemplateInfo : protected TemplateInfo
{
    public:
        ItemTemplateInfo();
        ItemTemplateInfo(const ItemTemplateInfo & iti);

        template<class Action>
        void persist(Action& a)
        {
            TemplateInfo::persist(a);

            Wt::Dbo::field(a, _class, "class");
            Wt::Dbo::field(a, _subClass, "subclass");
            Wt::Dbo::field(a, _unk0, "unk0");
            Wt::Dbo::field(a, _displayId, "displayid");
            Wt::Dbo::field(a, _quality, "Quality");
            Wt::Dbo::field(a, _flags, "Flags");
            Wt::Dbo::field(a, _buyCount, "BuyCount");
            Wt::Dbo::field(a, _buyPrice, "BuyPrice");
            Wt::Dbo::field(a, _sellPrice, "SellPrice");
            Wt::Dbo::field(a, _inventoryType, "InventoryType");
            Wt::Dbo::field(a, _allowableClass, "AllowableClass");
            Wt::Dbo::field(a, _allowableRace, "AllowableRace");
            Wt::Dbo::field(a, _itemLevel, "ItemLevel");
            Wt::Dbo::field(a, _requiredLevel, "RequiredLevel");
            Wt::Dbo::field(a, _requiredSkill, "RequiredSkill");
            Wt::Dbo::field(a, _requiredSkillRank, "RequiredSkillRank");
            Wt::Dbo::field(a, _requiredSpell, "requiredspell");
            Wt::Dbo::field(a, _requiredHonorRank, "requiredhonorrank");
            Wt::Dbo::field(a, _requiredCityRank, "RequiredCityRank");
            Wt::Dbo::field(a, _requiredReputationFaction, "RequiredReputationFaction");
            Wt::Dbo::field(a, _requiredReputationRank, "RequiredReputationRank");
            Wt::Dbo::field(a, _maxCount, "maxcount");
            Wt::Dbo::field(a, _stackable, "stackable");
            Wt::Dbo::field(a, _containerSlots, "ContainerSlots");
            Wt::Dbo::field(a, _statType[0], "stat_type1");
            Wt::Dbo::field(a, _statValue[1], "stat_value1");
            Wt::Dbo::field(a, _statType[1], "stat_type2");
            Wt::Dbo::field(a, _statValue[2], "stat_value2");
            Wt::Dbo::field(a, _statType[2], "stat_type3");
            Wt::Dbo::field(a, _statValue[3], "stat_value3");
            Wt::Dbo::field(a, _statType[3], "stat_type4");
            Wt::Dbo::field(a, _statValue[4], "stat_value4");
            Wt::Dbo::field(a, _statType[4], "stat_type5");
            Wt::Dbo::field(a, _statValue[4], "stat_value5");
            Wt::Dbo::field(a, _statType[5], "stat_type6");
            Wt::Dbo::field(a, _statValue[5], "stat_value6");
            Wt::Dbo::field(a, _statType[6], "stat_type7");
            Wt::Dbo::field(a, _statValue[6], "stat_value7");
            Wt::Dbo::field(a, _statType[7], "stat_type8");
            Wt::Dbo::field(a, _statValue[7], "stat_value8");
            Wt::Dbo::field(a, _statType[8], "stat_type9");
            Wt::Dbo::field(a, _statValue[8], "stat_value9");
            Wt::Dbo::field(a, _statType[9], "stat_type10");
            Wt::Dbo::field(a, _statValue[9], "stat_value10");
            Wt::Dbo::field(a, _dmgMin[0], "dmg_min1");
            Wt::Dbo::field(a, _dmgMax[0], "dmg_max1");
            Wt::Dbo::field(a, _dmgType[0], "dmg_type1");
            Wt::Dbo::field(a, _dmgMin[1], "dmg_min2");
            Wt::Dbo::field(a, _dmgMax[1], "dmg_max2");
            Wt::Dbo::field(a, _dmgType[1], "dmg_type2");
            Wt::Dbo::field(a, _dmgMin[2], "dmg_min3");
            Wt::Dbo::field(a, _dmgMax[2], "dmg_max3");
            Wt::Dbo::field(a, _dmgType[2], "dmg_type3");
            Wt::Dbo::field(a, _dmgMin[3], "dmg_min4");
            Wt::Dbo::field(a, _dmgMax[3], "dmg_max4");
            Wt::Dbo::field(a, _dmgType[3], "dmg_type4");
            Wt::Dbo::field(a, _dmgMin[4], "dmg_min5");
            Wt::Dbo::field(a, _dmgMax[4], "dmg_max5");
            Wt::Dbo::field(a, _dmgType[4], "dmg_type5");
            Wt::Dbo::field(a, _armor, "armor");
            Wt::Dbo::field(a, _holyRes, "holy_res");
            Wt::Dbo::field(a, _fireRes, "fire_res");
            Wt::Dbo::field(a, _natureRes, "nature_res");
            Wt::Dbo::field(a, _frostRes, "frost_res");
            Wt::Dbo::field(a, _shadowRes, "shadow_res");
            Wt::Dbo::field(a, _arcaneRes, "arcane_res");
            Wt::Dbo::field(a, _delay, "delay");
            Wt::Dbo::field(a, _ammoType, "ammo_type");
            Wt::Dbo::field(a, _rangedModRange, "RangedModRange");
            Wt::Dbo::field(a, _spellId[0], "spellid_1");
            Wt::Dbo::field(a, _spellTrigger[0], "spelltrigger_1");
            Wt::Dbo::field(a, _spellCharges[0], "spellcharges_1");
            Wt::Dbo::field(a, _spellPPMRate[0], "spellppmRate_1");
            Wt::Dbo::field(a, _spellCooldown[0], "spellcooldown_1");
            Wt::Dbo::field(a, _spellCategory[0], "spellcategory_1");
            Wt::Dbo::field(a, _spellCategoryCooldown[0], "spellcategorycooldown_1");
            Wt::Dbo::field(a, _spellId[1], "spellid_2");
            Wt::Dbo::field(a, _spellTrigger[1], "spelltrigger_2");
            Wt::Dbo::field(a, _spellCharges[1], "spellcharges_2");
            Wt::Dbo::field(a, _spellPPMRate[1], "spellppmRate_2");
            Wt::Dbo::field(a, _spellCooldown[1], "spellcooldown_2");
            Wt::Dbo::field(a, _spellCategory[1], "spellcategory_2");
            Wt::Dbo::field(a, _spellCategoryCooldown[1], "spellcategorycooldown_2");
            Wt::Dbo::field(a, _spellId[2], "spellid_3");
            Wt::Dbo::field(a, _spellTrigger[2], "spelltrigger_3");
            Wt::Dbo::field(a, _spellCharges[2], "spellcharges_3");
            Wt::Dbo::field(a, _spellPPMRate[2], "spellppmRate_3");
            Wt::Dbo::field(a, _spellCooldown[2], "spellcooldown_3");
            Wt::Dbo::field(a, _spellCategory[2], "spellcategory_3");
            Wt::Dbo::field(a, _spellCategoryCooldown[2], "spellcategorycooldown_3");
            Wt::Dbo::field(a, _spellId[3], "spellid_4");
            Wt::Dbo::field(a, _spellTrigger[3], "spelltrigger_4");
            Wt::Dbo::field(a, _spellCharges[3], "spellcharges_4");
            Wt::Dbo::field(a, _spellPPMRate[3], "spellppmRate_4");
            Wt::Dbo::field(a, _spellCooldown[3], "spellcooldown_4");
            Wt::Dbo::field(a, _spellCategory[3], "spellcategory_4");
            Wt::Dbo::field(a, _spellCategoryCooldown[3], "spellcategorycooldown_4");
            Wt::Dbo::field(a, _spellId[4], "spellid_5");
            Wt::Dbo::field(a, _spellTrigger[4], "spelltrigger_5");
            Wt::Dbo::field(a, _spellCharges[4], "spellcharges_5");
            Wt::Dbo::field(a, _spellPPMRate[4], "spellppmRate_5");
            Wt::Dbo::field(a, _spellCooldown[4], "spellcooldown_5");
            Wt::Dbo::field(a, _spellCategory[4], "spellcategory_5");
            Wt::Dbo::field(a, _spellCategoryCooldown[4], "spellcategorycooldown_5");
            Wt::Dbo::field(a, _bonding, "bonding");
            Wt::Dbo::field(a, _description, "description");
            Wt::Dbo::field(a, _pageText, "PageText");
            Wt::Dbo::field(a, _languageId, "LanguageID");
            Wt::Dbo::field(a, _pageMaterial, "PageMaterial");
            Wt::Dbo::field(a, _startQuest, "startquest");
            Wt::Dbo::field(a, _lockId, "lockid");
            Wt::Dbo::field(a, _material, "Material");
            Wt::Dbo::field(a, _sheath, "sheath");
            Wt::Dbo::field(a, _randomProperty, "RandomProperty");
            Wt::Dbo::field(a, _randomSuffix, "RandomSuffix");
            Wt::Dbo::field(a, _block, "block");
            Wt::Dbo::field(a, _itemSet, "itemset");
            Wt::Dbo::field(a, _maxDurability, "MaxDurability");
            Wt::Dbo::field(a, _area, "area");
            Wt::Dbo::field(a, _map, "Map");
            Wt::Dbo::field(a, _bagFamily, "BagFamily");
            Wt::Dbo::field(a, _totemCategory, "TotemCategory");
            Wt::Dbo::field(a, _socketColor[0], "socketColor_1");
            Wt::Dbo::field(a, _socketContent[0], "socketContent_1");
            Wt::Dbo::field(a, _socketColor[1], "socketColor_2");
            Wt::Dbo::field(a, _socketContent[1], "socketContent_2");
            Wt::Dbo::field(a, _socketColor[2], "socketColor_3");
            Wt::Dbo::field(a, _socketContent[2], "socketContent_3");
            Wt::Dbo::field(a, _socketBonus, "socketBonus");
            Wt::Dbo::field(a, _gemProperties, "GemProperties");
            Wt::Dbo::field(a, _requiredDisenchantSkill, "RequiredDisenchantSkill");
            Wt::Dbo::field(a, _armorDamageModifier, "ArmorDamageModifier");
            Wt::Dbo::field(a, _scriptName, "ScriptName");
            Wt::Dbo::field(a, _disenchantId, "DisenchantID");
            Wt::Dbo::field(a, _foodType, "FoodType");
            Wt::Dbo::field(a, _minMoneyLoot, "minMoneyLoot");
            Wt::Dbo::field(a, _maxMoneyLoot, "maxMoneyLoot");
            Wt::Dbo::field(a, _duration, "Duration");
        }

        virtual Wt::WContainerWidget * CreateContainer() const;

        const int & GetClass() const { return _class; }
        const int & GetSubClass() const { return _subClass; }
        const int & GetUnk0() const { return _unk0; }
        const int & GetDisplayId() const { return _displayId; }
        const int & GetQuality() const { return _quality; }
        const long & GetFlags() const { return _flags; }
        const int & GetBuyCount() const { return _buyCount; }
        const long & GetBuyPrice() const { return _buyPrice; }
        const long & GetSellPrice() const { return _sellPrice; }
        const int & GetInventoryType() const { return _inventoryType; }
        const int & GetAllowableClass() const { return _allowableClass; }
        const int & GetAllowableRace() const { return _allowableRace; }
        const int & GetItemLevel() const { return _itemLevel; }
        const int & GetRequiredLevel() const { return _requiredLevel; }
        const int & GetRequiredSkill() const { return _requiredSkill; }
        const int & GetRequiredSkillRank() const { return _requiredSkillRank; }
        const int & GetRequiredSpell() const { return _requiredSpell; }
        const int & GetRequiredHonorRank() const { return _requiredHonorRank; }
        const int & GetRequiredCityRank() const { return _requiredCityRank; }
        const int & GetRequiredReputationFaction() const { return _requiredReputationFaction; }
        const int & GetRequiredReputationRank() const { return _requiredReputationRank; }
        const int & GetMaxCount() const { return _maxCount; }
        const int & GetStackable() const { return _stackable; }
        const int & GetContainerSlots() const { return _containerSlots; }
        const int & GetStatType(unsigned int i) const { return _statType[i]; }
        const int & GetStatValue(unsigned int i) const { return _statValue[i]; }
        const float & GetDmgMin(unsigned int i) const { return _dmgMin[i]; }
        const float & GetDmgMax(unsigned int i) const { return _dmgMax[i]; }
        const int & GetDmgType(unsigned int i) const { return _dmgType[i]; }
        const int & GetArmor() const { return _armor; }
        const int & GetHolyRes() const { return _holyRes; }
        const int & GetFireRes() const { return _fireRes; }
        const int & GetNatureRes() const { return _natureRes; }
        const int & GetFrostRes() const { return _frostRes; }
        const int & GetShadowRes() const { return _shadowRes; }
        const int & GetArcaneRes() const { return _arcaneRes; }
        const int & GetDelay() const { return _delay; }
        const int & GetAmmoType() const { return _ammoType; }
        const float & GetRangedModRange() const { return _rangedModRange; }
        const int & GetSpellId(unsigned int i) const { return _spellId[i]; }
        const int & GetSpellTrigger(unsigned int i) const { return _spellTrigger[i]; }
        const int & GetSpellCharges(unsigned int i) const { return _spellCharges[i]; }
        const float & GetSpellPPMRate(unsigned int i) const { return _spellPPMRate[i]; }
        const int & GetSpellCooldown(unsigned int i) const { return _spellCooldown[i]; }
        const int & GetSpellCategory(unsigned int i) const { return _spellCategory[i]; }
        const int & GetSpellCategoryCooldown(unsigned int i) const { return _spellCategoryCooldown[i]; }
        const int & GetBonding() const { return _bonding; }
        const std::string & GetDescription() const { return _description; }
        const int & GetPageText() const { return _pageText; }
        const int & GetLanguageId() const { return _languageId; }
        const int & GetPageMaterial() const { return _pageMaterial; }
        const int & GetStartQuest() const { return _startQuest; }
        const int & GetLockId() const { return _lockId; }
        const int & GetMaterial() const { return _material; }
        const int & GetSheath() const { return _sheath; }
        const int & GetRandomProperty() const { return _randomProperty; }
        const int & GetRandomSuffix() const { return _randomSuffix; }
        const int & GetBlock() const { return _block; }
        const int & GetItemSet() const { return _itemSet; }
        const int & GetMaxDurability() const { return _maxDurability; }
        const int & GetArea() const { return _area; }
        const int & GetMap() const { return _map; }
        const int & GetBagFamily() const { return _bagFamily; }
        const int & GetTotemCategory() const { return _totemCategory; }
        const int & GetSocketColor(unsigned int i) const { return _socketColor[i]; }
        const int & GetSocketContent(unsigned int i) const { return _socketContent[i]; }
        const int & GetSocketBonus() const { return _socketBonus; }
        const int & GetGemProperties() const { return _gemProperties; }
        const int & GetRequiredDisenchantSkill() const { return _requiredDisenchantSkill; }
        const float & GetArmorDamageModifier() const { return _armorDamageModifier; }
        const std::string & GetScriptName() const { return _scriptName; }
        const int & GetDisenchantId() const { return _disenchantId; }
        const int & GetFoodType() const { return _foodType; }
        const long & GetMinMoneyLoot() const { return _minMoneyLoot; }
        const long & GetMaxMoneyLoot() const { return _maxMoneyLoot; }
        const long & GetDuration() const { return _duration; }

    private:
        int _class;
        int _subClass;
        int _unk0;
        int _displayId;
        int _quality;
        long _flags;
        int _buyCount;
        long _buyPrice;
        long _sellPrice;
        int _inventoryType;
        int _allowableClass;
        int _allowableRace;
        int _itemLevel;
        int _requiredLevel;
        int _requiredSkill;
        int _requiredSkillRank;
        int _requiredSpell;
        int _requiredHonorRank;
        int _requiredCityRank;
        int _requiredReputationFaction;
        int _requiredReputationRank;
        int _maxCount;
        int _stackable;
        int _containerSlots;
        int _statType[10];
        int _statValue[10];
        float _dmgMin[5];
        float _dmgMax[5];
        int _dmgType[5];
        int _armor;
        int _holyRes;
        int _fireRes;
        int _natureRes;
        int _frostRes;
        int _shadowRes;
        int _arcaneRes;
        int _delay;
        int _ammoType;
        float _rangedModRange;
        int _spellId[5];
        int _spellTrigger[5];
        int _spellCharges[5];
        float _spellPPMRate[5];
        int _spellCooldown[5];
        int _spellCategory[5];
        int _spellCategoryCooldown[5];
        int _bonding;
        std::string _description;
        int _pageText;
        int _languageId;
        int _pageMaterial;
        int _startQuest;
        int _lockId;
        int _material;
        int _sheath;
        int _randomProperty;
        int _randomSuffix;
        int _block;
        int _itemSet;
        int _maxDurability;
        int _area;
        int _map;
        int _bagFamily;
        int _totemCategory;
        int _socketColor[3];
        int _socketContent[3];
        int _socketBonus;
        int _gemProperties;
        int _requiredDisenchantSkill;
        float _armorDamageModifier;
        std::string _scriptName;
        int _disenchantId;
        int _foodType;
        long _minMoneyLoot;
        long _maxMoneyLoot;
        long _duration;
};

// disable default version and id fields for SearchResult class
namespace Wt
{
    namespace Dbo
    {
        template<>
        struct dbo_traits<TemplateInfo> : public dbo_default_traits
        {
            static long invalidId() { return 0; }
            static const char *surrogateIdField() { return NULL; }
            static const char *versionField() { return NULL; }
        };

        template<>
        struct dbo_traits<CreatureTemplateInfo> : public dbo_default_traits
        {
            static long invalidId() { return 0; }
            static const char *surrogateIdField() { return NULL; }
            static const char *versionField() { return NULL; }
        };

        template<>
        struct dbo_traits<GameObjectTemplateInfo> : public dbo_default_traits
        {
            static long invalidId() { return 0; }
            static const char *surrogateIdField() { return NULL; }
            static const char *versionField() { return NULL; }
        };

        template<>
        struct dbo_traits<QuestTemplateInfo> : public dbo_default_traits
        {
            static long invalidId() { return 0; }
            static const char *surrogateIdField() { return NULL; }
            static const char *versionField() { return NULL; }
        };

        template<>
        struct dbo_traits<SpellTemplateInfo> : public dbo_default_traits
        {
            static long invalidId() { return 0; }
            static const char *surrogateIdField() { return NULL; }
            static const char *versionField() { return NULL; }
        };

        template<>
        struct dbo_traits<ItemTemplateInfo> : public dbo_default_traits
        {
            static long invalidId() { return 0; }
            static const char *surrogateIdField() { return NULL; }
            static const char *versionField() { return NULL; }
        };
    }
}

#endif // H_dboClasses
