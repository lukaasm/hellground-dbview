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

#ifndef H_DboClasses
#define H_DboClasses

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

        long GetHeroicEntry() const { return _heroicEntry; }
        long GetKillCredit() const { return _killCredit; }
        long GetModelIdA(unsigned int i) const { return (i < 2) ? _modelIdA[i] : 0; }
        long GetModelIdH(unsigned int i) const { return (i < 2) ? _modelIdH[i] : 0; }
        const std::string & GetSubName() const { return _subName; }
        const std::string & GetIconName() const { return _iconName; }
        int GetMinLevel() const { return _minLevel; }
        int GetMaxLevel() const { return _maxLevel; }
        double GetMinHealth() const { return _minHealth; }
        double GetMaxHealth() const { return _maxHealth; }
        double GetMinMana() const { return _minMana; }
        double GetMaxMana() const { return _maxMana; }
        long GetArmor() const { return _armor; }
        int GetFactionA() const { return _factionA; }
        int GetFactionH() const { return _factionH; }
        double GetNpcFlags() const { return _npcFlags; }
        float GetSpeed() const { return _speed; }
        float GetScale() const { return _scale; }
        int GetRank() const { return _rank; }
        float GetMinDmg() const { return _minDmg; }
        float GetMaxDmg() const { return _maxDmg; }
        int GetDmgSchool() const { return _dmgSchool; }
        double GetAttackPower() const { return _attackPower; }
        double GetBaseAttackTime() const { return _baseAttackTime; }
        double GetRangeAttackTime() const { return _rangeAttackTime; }
        double GetUnitFlags() const { return _unitFlags; }
        double GetDynamicFlags() const { return _dynamicFlags; }
        int GetFamily() const { return _family; }
        int GetTrainerType() const { return _trainerType; }
        int GetTrainerSpell() const { return _trainerSpell; }
        int GetClass() const { return _class; }
        int GetRace() const { return _race; }
        float GetMinRangeDmg() const { return _minRangeDmg; }
        float GetMaxRangeDmg() const { return _maxRangeDmg; }
        long GetRangeAttackPower() const { return _rangeAttackPower; }
        int GetType() const { return _type; }
        double GetTypeFlags() const { return _typeFlags; }
        int GetLootId() const { return _lootId; }
        int GetPickPocketLoot() const { return _pickPocketLoot; }
        int GetSkinLoot() const { return _skinLoot; }
        int GetResistance(unsigned int i) const { return (i < 6) ? _resistance[i] : 0; }
        int GetSpell(unsigned int i) const { return (i < 5 ) ? _spell[i] : 0; }
        int GetPetSpellDataId() const { return _petSpellDataId; }
        long GetMinGold() const { return _minGold; }
        long GetMaxGold() const { return _maxGold; }
        const std::string & GetAiName() const { return _aiName; }
        int GetMovementType() const { return _movementType; }
        int GetInhabitType() const { return _inhabitType; }
        int GetRacialLeader() const { return _racialLeader; }
        int GetRegenHealth() const { return _regenHealth; }
        int GetEquipmentId() const { return _equipmentId; }
        double GetMechanicImmuneMask() const { return _mechanicImmuneMask; }
        double GetFlagsExtra() const { return _flagsExtra; }
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
        GameObjectTemplateInfo(const GameObjectTemplateInfo & cti);

        template<class Action>
        void persist(Action& a)
        {
            TemplateInfo::persist(a);
        }

        virtual Wt::WContainerWidget * CreateContainer() const;

    private:
};

class QuestTemplateInfo : protected TemplateInfo
{
    public:
        QuestTemplateInfo();
        QuestTemplateInfo(const QuestTemplateInfo & cti);

        template<class Action>
        void persist(Action& a)
        {
            TemplateInfo::persist(a);
        }

        virtual Wt::WContainerWidget * CreateContainer() const;

    private:
};

class SpellTemplateInfo : protected TemplateInfo
{
    public:
        SpellTemplateInfo();
        SpellTemplateInfo(const SpellTemplateInfo & cti);

        template<class Action>
        void persist(Action& a)
        {
            TemplateInfo::persist(a);
        }

        virtual Wt::WContainerWidget * CreateContainer() const;

    private:
};

class ItemTemplateInfo : protected TemplateInfo
{
    public:
        ItemTemplateInfo();
        ItemTemplateInfo(const ItemTemplateInfo & cti);

        template<class Action>
        void persist(Action& a)
        {
            TemplateInfo::persist(a);
        }

        virtual Wt::WContainerWidget * CreateContainer() const;

    private:
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

#endif // H_DboClasses
