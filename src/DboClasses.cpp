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

#include "DboClasses.h"

#include <boost/lexical_cast.hpp>
#include <Wt/Dbo/backend/MySQL.h>
#include <Wt/WContainerWidget>
#include <Wt/WTable>
#include <Wt/WText>

#include "Language.h"

template<class T>
std::string TemplateInfo::GetAsString(T & value) const
{
    return boost::lexical_cast<std::string>(value);
}

Wt::WText* TemplateInfo::addWText(Wt::WContainerWidget * cont, Wt::WString text) const
{
    Wt::WText * tmpText = new Wt::WText(text);
    cont->addWidget(tmpText);
    return tmpText;
}

Wt::WText* TemplateInfo::addWText(Wt::WTableCell * cont, Wt::WString text) const
{
    return addWText((Wt::WContainerWidget*)cont, text);
}

CreatureTemplateInfo::CreatureTemplateInfo()
    : TemplateInfo(), _heroicEntry(0), _killCredit(0), _subName(""), _iconName(""), _minLevel(0),
    _maxLevel(0), _minHealth(0), _maxHealth(0), _minMana(0), _maxMana(0), _armor(0), _factionA(0),
    _factionH(0), _npcFlags(0), _speed(0), _scale(0), _rank(0), _minDmg(0), _maxDmg(0), _dmgSchool(0),
    _attackPower(0), _baseAttackTime(0), _rangeAttackTime(0), _unitFlags(0), _dynamicFlags(0), _family(0),
    _trainerType(0), _trainerSpell(0), _class(0), _race(0), _minRangeDmg(0), _maxRangeDmg(0),
    _rangeAttackPower(0), _type(0), _typeFlags(0), _lootId(0), _pickPocketLoot(0), _skinLoot(),
    _petSpellDataId(0), _minGold(0), _maxGold(0), _aiName(""), _movementType(0), _inhabitType(0),
    _racialLeader(0), _regenHealth(0), _equipmentId(0), _mechanicImmuneMask(0), _flagsExtra(0), _scriptName("")
{
    _modelIdA[0] = 0;
    _modelIdA[1] = 0;

    _modelIdH[0] = 0;
    _modelIdH[1] = 0;

    _resistance[0] = 0;
    _resistance[1] = 0;
    _resistance[2] = 0;
    _resistance[3] = 0;
    _resistance[4] = 0;
    _resistance[5] = 0;

    _spell[0] = 0;
    _spell[1] = 0;
    _spell[2] = 0;
    _spell[3] = 0;
    _spell[4] = 0;
}

CreatureTemplateInfo::CreatureTemplateInfo(const CreatureTemplateInfo & cti)
    : TemplateInfo(cti.GetEntry(), cti.GetName())
{
    _heroicEntry = cti.GetHeroicEntry();
    _killCredit = cti.GetKillCredit();
    _modelIdA[0] = cti.GetModelIdA(0);
    _modelIdA[1] = cti.GetModelIdA(1);
    _modelIdH[0] = cti.GetModelIdH(0);
    _modelIdH[1] = cti.GetModelIdH(1);
    _subName = cti.GetSubName();
    _iconName = cti.GetIconName();
    _minLevel = cti.GetMinLevel();
    _maxLevel = cti.GetMaxLevel();
    _minHealth = cti.GetMinHealth();
    _maxHealth = cti.GetMaxHealth();
    _minMana = cti.GetMinMana();
    _maxMana = cti.GetMaxMana();
    _armor = cti.GetArmor();
    _factionA = cti.GetFactionA();
    _factionH = cti.GetFactionH();
    _npcFlags = cti.GetNpcFlags();
    _speed = cti.GetSpeed();
    _scale = cti.GetScale();
    _rank = cti.GetRank();
    _minDmg = cti.GetMinDmg();
    _maxDmg = cti.GetMaxDmg();
    _dmgSchool = cti.GetDmgSchool();
    _attackPower = cti.GetAttackPower();
    _baseAttackTime = cti.GetBaseAttackTime();
    _rangeAttackTime = cti.GetRangeAttackTime();
    _unitFlags = cti.GetUnitFlags();
    _dynamicFlags = cti.GetDynamicFlags();
    _family = cti.GetFamily();
    _trainerType = cti.GetTrainerType();
    _trainerSpell = cti.GetTrainerSpell();
    _class = cti.GetClass();
    _race = cti.GetRace();
    _minRangeDmg = cti.GetMinRangeDmg();
    _maxRangeDmg = cti.GetMaxRangeDmg();
    _rangeAttackPower = cti.GetRangeAttackPower();
    _type = cti.GetType();
    _typeFlags = cti.GetTypeFlags();
    _lootId = cti.GetLootId();
    _pickPocketLoot = cti.GetPickPocketLoot();
    _skinLoot = cti.GetSkinLoot();

    for (int i = 0; i < 6; ++i)
        _resistance[i] = cti.GetResistance(i);

    for (int i = 0; i < 5; ++i)
        _spell[i] = cti.GetSpell(i);

    _petSpellDataId = cti.GetPetSpellDataId();
    _minGold = cti.GetMinGold();
    _maxGold = cti.GetMaxGold();
    _aiName = cti.GetAiName();
    _movementType = cti.GetMovementType();
    _inhabitType = cti.GetInhabitType();
    _racialLeader = cti.GetRacialLeader();
    _regenHealth = cti.GetRegenHealth();
    _equipmentId = cti.GetEquipmentId();
    _mechanicImmuneMask = cti.GetMechanicImmuneMask();
    _flagsExtra = cti.GetFlagsExtra();
    _scriptName = cti.GetScriptName();
}

Wt::WContainerWidget * CreatureTemplateInfo::CreateContainer() const
{
    Wt::WContainerWidget * cInfoCont = new Wt::WContainerWidget();
    Wt::WContainerWidget * tmpCont;

    tmpCont = new Wt::WContainerWidget(cInfoCont);
    tmpCont->setStyleClass("details dethead");
    tmpCont->addWidget(new Wt::WText(Wt::WString::LANG_DETAIL_TITLE.arg(Wt::WString::LANG_CREATURE).arg(GetName()).arg(GetEntry())));

    tmpCont = new Wt::WContainerWidget(cInfoCont);
    tmpCont->setStyleClass("details detcenter");

    tmpCont = new Wt::WContainerWidget(cInfoCont);
    tmpCont->setStyleClass("details detbottom");

    Wt::WTable * tmpTable = new Wt::WTable(tmpCont);
    tmpTable->setStyleClass("details");
    tmpTable->setHeaderCount(0);

    addWText(tmpTable->elementAt(0, 0), Wt::WString::LANG_ENTRY);
    addWText(tmpTable->elementAt(0, 1), GetAsString(GetEntry()));
    addWText(tmpTable->elementAt(0, 2), Wt::WString::LANG_DETAIL_HEROIC_ENTRY);
    addWText(tmpTable->elementAt(0, 3), GetAsString(_heroicEntry));
    addWText(tmpTable->elementAt(0, 4), Wt::WString::LANG_DETAIL_KILL_CREDIT);
    addWText(tmpTable->elementAt(0, 5), GetAsString(_killCredit));
    addWText(tmpTable->elementAt(0, 6), Wt::WString::LANG_DETAIL_RANK);
    addWText(tmpTable->elementAt(0, 7), GetAsString(_rank));

    addWText(tmpTable->elementAt(1, 0), Wt::WString::LANG_NAME);
    addWText(tmpTable->elementAt(1, 1), GetName());
    addWText(tmpTable->elementAt(1, 2), Wt::WString::LANG_DETAIL_SUB_NAME);
    addWText(tmpTable->elementAt(1, 3), _subName);
    addWText(tmpTable->elementAt(1, 4), Wt::WString::LANG_DETAIL_AI_NAME);
    addWText(tmpTable->elementAt(1, 5), _aiName);
    addWText(tmpTable->elementAt(1, 6), Wt::WString::LANG_DETAIL_SCRIPT_NAME);
    addWText(tmpTable->elementAt(1, 7), _scriptName);

    addWText(tmpTable->elementAt(2, 0), Wt::WString::LANG_DETAIL_MODEL_ID_A);
    addWText(tmpTable->elementAt(2, 1), GetAsString(_modelIdA[0]));
    addWText(tmpTable->elementAt(2, 2), Wt::WString::LANG_DETAIL_MODEL_ID_A);
    addWText(tmpTable->elementAt(2, 3), GetAsString(_modelIdA[1]));
    addWText(tmpTable->elementAt(2, 4), Wt::WString::LANG_DETAIL_MODEL_ID_H);
    addWText(tmpTable->elementAt(2, 5), GetAsString(_modelIdH[0]));
    addWText(tmpTable->elementAt(2, 6), Wt::WString::LANG_DETAIL_MODEL_ID_H);
    addWText(tmpTable->elementAt(2, 7), GetAsString(_modelIdH[1]));

    addWText(tmpTable->elementAt(3, 0), Wt::WString::LANG_DETAIL_FACTION_A);
    addWText(tmpTable->elementAt(3, 1), GetAsString(_factionA));
    addWText(tmpTable->elementAt(3, 2), Wt::WString::LANG_DETAIL_FACTION_H);
    addWText(tmpTable->elementAt(3, 3), GetAsString(_factionH));
    addWText(tmpTable->elementAt(3, 4), Wt::WString::LANG_DETAIL_MIN_LVL);
    addWText(tmpTable->elementAt(3, 5), GetAsString(_minLevel));
    addWText(tmpTable->elementAt(3, 6), Wt::WString::LANG_DETAIL_MAX_LVL);
    addWText(tmpTable->elementAt(3, 7), GetAsString(_maxLevel));

    addWText(tmpTable->elementAt(4, 0), Wt::WString::LANG_DETAIL_MIN_HEALTH);
    addWText(tmpTable->elementAt(4, 1), GetAsString(_minHealth));
    addWText(tmpTable->elementAt(4, 2), Wt::WString::LANG_DETAIL_MAX_HEALTH);
    addWText(tmpTable->elementAt(4, 3), GetAsString(_maxHealth));
    addWText(tmpTable->elementAt(4, 4), Wt::WString::LANG_DETAIL_MIN_MANA);
    addWText(tmpTable->elementAt(4, 5), GetAsString(_minMana));
    addWText(tmpTable->elementAt(4, 6), Wt::WString::LANG_DETAIL_MAX_MANA);
    addWText(tmpTable->elementAt(4, 7), GetAsString(_maxMana));

    addWText(tmpTable->elementAt(5, 0), Wt::WString::LANG_DETAIL_RACE);
    addWText(tmpTable->elementAt(5, 1), GetAsString(_race));
    addWText(tmpTable->elementAt(5, 2), Wt::WString::LANG_DETAIL_CLASS);
    addWText(tmpTable->elementAt(5, 3), GetAsString(_class));
    addWText(tmpTable->elementAt(5, 4), Wt::WString::LANG_DETAIL_FAMILY);
    addWText(tmpTable->elementAt(5, 5), GetAsString(_family));
    addWText(tmpTable->elementAt(5, 6), Wt::WString::LANG_DETAIL_TYPE);
    addWText(tmpTable->elementAt(5, 7), GetAsString(_type));

    addWText(tmpTable->elementAt(6, 0), Wt::WString::LANG_DETAIL_ARMOR);
    addWText(tmpTable->elementAt(6, 1), GetAsString(_armor));
    addWText(tmpTable->elementAt(6, 2), Wt::WString::LANG_DETAIL_SPEED);
    addWText(tmpTable->elementAt(6, 3), GetAsString(_speed));
    addWText(tmpTable->elementAt(6, 4), Wt::WString::LANG_DETAIL_SCALE);
    addWText(tmpTable->elementAt(6, 5), GetAsString(_scale));
    addWText(tmpTable->elementAt(6, 6), Wt::WString::LANG_DETAIL_EQUIPMENT_ID);
    addWText(tmpTable->elementAt(6, 7), GetAsString(_equipmentId));

    addWText(tmpTable->elementAt(7, 0), Wt::WString::LANG_DETAIL_MIN_DMG);
    addWText(tmpTable->elementAt(7, 1), GetAsString(_minDmg));
    addWText(tmpTable->elementAt(7, 2), Wt::WString::LANG_DETAIL_MAX_DMG);
    addWText(tmpTable->elementAt(7, 3), GetAsString(_maxDmg));
    addWText(tmpTable->elementAt(7, 4), Wt::WString::LANG_DETAIL_ATTACK_POWER);
    addWText(tmpTable->elementAt(7, 5), GetAsString(_attackPower));
    addWText(tmpTable->elementAt(7, 6), Wt::WString::LANG_DETAIL_ATTACK_TIME);
    addWText(tmpTable->elementAt(7, 7), GetAsString(_baseAttackTime));

    addWText(tmpTable->elementAt(8, 0), Wt::WString::LANG_DETAIL_RANGED_MIN_DMG);
    addWText(tmpTable->elementAt(8, 1), GetAsString(_minRangeDmg));
    addWText(tmpTable->elementAt(8, 2), Wt::WString::LANG_DETAIL_RANGED_MAX_DMG);
    addWText(tmpTable->elementAt(8, 3), GetAsString(_maxRangeDmg));
    addWText(tmpTable->elementAt(8, 4), Wt::WString::LANG_DETAIL_RANGED_ATTACK_POWER);
    addWText(tmpTable->elementAt(8, 5), GetAsString(_rangeAttackPower));
    addWText(tmpTable->elementAt(8, 6), Wt::WString::LANG_DETAIL_RANGED_ATTACK_TIME);
    addWText(tmpTable->elementAt(8, 7), GetAsString(_rangeAttackTime));

    addWText(tmpTable->elementAt(9, 0), Wt::WString::LANG_DETAIL_DMG_SCHOOL);
    addWText(tmpTable->elementAt(9, 1), GetAsString(_dmgSchool));
    addWText(tmpTable->elementAt(9, 2), Wt::WString::LANG_DETAIL_MIN_GOLD);
    addWText(tmpTable->elementAt(9, 3), GetAsString(_minGold));
    addWText(tmpTable->elementAt(9, 4), Wt::WString::LANG_DETAIL_MAX_GOLD);
    addWText(tmpTable->elementAt(9, 5), GetAsString(_maxGold));
    addWText(tmpTable->elementAt(9, 6), Wt::WString::LANG_DETAIL_RACIAL_LEADER);
    addWText(tmpTable->elementAt(9, 7), GetAsString(_racialLeader));
/*
    addWText(tmpTable->elementAt(10, 0), Wt::WString::);
    addWText(tmpTable->elementAt(10, 1), );
    addWText(tmpTable->elementAt(10, 2), Wt::WString::);
    addWText(tmpTable->elementAt(10, 3), );
    addWText(tmpTable->elementAt(10, 4), Wt::WString::);
    addWText(tmpTable->elementAt(10, 5), );
    addWText(tmpTable->elementAt(10, 6), Wt::WString::);
    addWText(tmpTable->elementAt(10, 7), );
*/
    return cInfoCont;
}
