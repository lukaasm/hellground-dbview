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

// Creature Template Info

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

// Gameobject Template Info

GameObjectTemplateInfo::GameObjectTemplateInfo()
    : TemplateInfo(), _type(0), _displayId(0), _castBarCaption(""), _faction(0), _flags(0), _size(0), _scriptName("")
{
    for (int i = 0; i < 24; ++i)
        _data[i] = 0;
}

GameObjectTemplateInfo::GameObjectTemplateInfo(const GameObjectTemplateInfo & gti)
    : TemplateInfo(gti.GetEntry(), gti.GetName())
{
    _type = gti.GetType();
    _displayId = gti.GetDisplayId();
    _castBarCaption = gti.GetCastBarCaption();
    _faction = gti.GetFaction();
    _flags = gti.GetFlags();
    _size = gti.GetSize();

    for (int i = 0; i < 24; ++i)
        _data[i] = gti.GetData(i);

    _scriptName = gti.GetScriptName();
}

Wt::WContainerWidget * GameObjectTemplateInfo::CreateContainer() const
{
    return NULL;
}

// Quest Template Info

QuestTemplateInfo::QuestTemplateInfo()
    : TemplateInfo(), _method(0), _zoneOrSort(0), _skillOrClass(0), _minLevel(0), _questLevel(0), _type(0),
    _requiredRaces(0), _requiredSkillValue(0), _repObjectiveFaction(0), _repObjectiveValue(0), _requiredMinRepFaction(0),
    _requiredMinRepValue(0), _requiredMaxRepFaction(0), _requiredMaxRepValue(0), _suggestedPlayers(0),_limitTime(0),
    _questFlags(0), _specialFlags(0), _charTitleId(0), _prevQuestId(0), _nextQuestId(0), _exclusiveGroup(0),
    _nextQuestInChain(0), _srcItemId(0), _srcItemCount(0), _srcSpell(0), _details(""), _objectives(""),
    _offerRewardText(""), _requestItemsText(""), _endText(""), _rewHonorableKills(0), _rewOrReqMoney(0),
    _rewMoneyMaxLevel(0), _rewSpell(0), _rewSpellCast(0), _rewMailTemplateId(0), _rewMailDelaySecs(0), _pointMapId(0),
    _pointX(0.0f), _pointY(0.0f), _pointOpt(0), _incompleteEmote(0), _completeEmote(0), _startScript(0), _completeScript(0)
{
    for (int i = 0; i < 4; ++i)
    {
        _objectiveText[i] = "";
        _reqItemId[i] = 0;
        _reqItemCount[i] = 0;
        _reqSourceId[i] = 0;
        _reqSourceCount[i] = 0;
        _reqSourceRef[i] = 0;
        _reqCreatureOrGOId[i] = 0;
        _reqCreatureOrGOCount[i] = 0;
        _reqSpellCast[i] = 0;
        _rewItemId[i] = 0;
        _rewItemCount[i] = 0;
        _detailsEmote[i] = 0;
        _offerRewardEmote[i] = 0;

        _rewChoiceItemId[i] = 0;
        _rewChoiceItemCount[i] = 0;
        _rewRepFaction[i] = 0;
        _rewRepValue[i] = 0;
    }

    _rewChoiceItemId[4] = 0;
    _rewChoiceItemCount[4] = 0;
    _rewChoiceItemId[5] = 0;
    _rewChoiceItemCount[5] = 0;
    _rewRepFaction[4] = 0;
    _rewRepValue[4] = 0;
}

QuestTemplateInfo::QuestTemplateInfo(const QuestTemplateInfo & qti)
    : TemplateInfo(qti.GetEntry(), qti.GetName())
{
    _method = qti.GetMethod();
    _zoneOrSort = qti.GetZoneOrSort();
    _skillOrClass = qti.GetSkillOrClass();
    _minLevel = qti.GetMinLevel();
    _questLevel = qti.GetQuestLevel();
    _type = qti.GetType();
    _requiredRaces = qti.GetRequiredRaces();
    _requiredSkillValue = qti.GetRequiredSkillValue();
    _repObjectiveFaction = qti.GetRepObjectiveFaction();
    _repObjectiveValue = qti.GetRepObjectiveValue();
    _requiredMinRepFaction = qti.GetRequiredMinRepFaction();
    _requiredMinRepValue = qti.GetRequiredMinRepValue();
    _requiredMaxRepFaction = qti.GetRequiredMaxRepFaction();
    _requiredMaxRepValue = qti.GetRequiredMaxRepValue();
    _suggestedPlayers = qti.GetSuggestedPlayers();
    _limitTime = qti.GetLimitTime();
    _questFlags = qti.GetQuestFlags();
    _specialFlags = qti.GetSpecialFlags();
    _charTitleId = qti.GetCharTitleId();
    _prevQuestId = qti.GetPrevQuestId();
    _nextQuestId = qti.GetNextQuestId();
    _exclusiveGroup = qti.GetExclusiveGroup();
    _nextQuestInChain = qti.GetNextQuestInChain();
    _srcItemId = qti.GetSrcItemId();
    _srcItemCount = qti.GetSrcItemCount();
    _srcSpell = qti.GetSrcSpell();
    _details = qti.GetDetails();
    _objectives = qti.GetObjectives();
    _offerRewardText = qti.GetOfferRewardText();
    _requestItemsText = qti.GetRequestItemsText();
    _endText = qti.GetEndText();
    _rewHonorableKills = qti.GetRewHonorableKills();
    _rewOrReqMoney = qti.GetRewOrReqMoney();
    _rewMoneyMaxLevel = qti.GetRewMoneyMaxLevel();
    _rewSpell = qti.GetRewSpell();
    _rewSpellCast = qti.GetRewSpellCast();
    _rewMailTemplateId = qti.GetRewMailTemplateId();
    _rewMailDelaySecs = qti.GetRewMailDelaySecs();
    _pointMapId = qti.GetPointMapId();
    _pointX = qti.GetPointX();
    _pointY = qti.GetPointY();
    _pointOpt = qti.GetPointOpt();
    _incompleteEmote = qti.GetIncompleteEmote();
    _completeEmote = qti.GetCompleteEmote();
    _startScript = qti.GetStartScript();
    _completeScript = qti.GetCompleteScript();

    for (int i = 0; i < 4; ++i)
    {
        _objectiveText[i] = qti.GetObjectiveText(i);
        _reqItemId[i] = qti.GetReqItemId(i);
        _reqItemCount[i] = qti.GetReqItemCount(i);
        _reqSourceId[i] = qti.GetReqSourceId(i);
        _reqSourceCount[i] = qti.GetReqSourceCount(i);
        _reqSourceRef[i] = qti.GetReqSourceRef(i);
        _reqCreatureOrGOId[i] = qti.GetReqCreatureOrGOId(i);
        _reqCreatureOrGOCount[i] = qti.GetReqCreatureOrGOCount(i);
        _reqSpellCast[i] = qti.GetReqSpellCast(i);
        _rewItemId[i] = qti.GetRewItemId(i);
        _rewItemCount[i] = qti.GetRewItemCount(i);
        _detailsEmote[i] = qti.GetDetailsEmote(i);
        _offerRewardEmote[i] = qti.GetOfferRewardEmote(i);

        _rewChoiceItemId[i] = qti.GetRewChoiceItemId(i);
        _rewChoiceItemCount[i] = qti.GetRewChoiceItemCount(i);
        _rewRepFaction[i] = qti.GetRewRepFaction(i);
        _rewRepValue[i] = qti.GetRewRepValue(i);
    }

    _rewChoiceItemId[4] = qti.GetRewChoiceItemId(4);
    _rewChoiceItemCount[4] = qti.GetRewChoiceItemCount(4);
    _rewChoiceItemId[5] = qti.GetRewChoiceItemId(5);
    _rewChoiceItemCount[5] = qti.GetRewChoiceItemCount(5);
    _rewRepFaction[4] = qti.GetRewRepFaction(4);
    _rewRepValue[4] = qti.GetRewRepValue(4);
}

Wt::WContainerWidget * QuestTemplateInfo::CreateContainer() const
{
    return NULL;
}

// Spell Template Info

SpellTemplateInfo::SpellTemplateInfo()
    : TemplateInfo()
{

}

SpellTemplateInfo::SpellTemplateInfo(const SpellTemplateInfo & sti)
    : TemplateInfo(sti.GetEntry(), sti.GetName())
{

}

Wt::WContainerWidget * SpellTemplateInfo::CreateContainer() const
{
    return NULL;
}

// Item Template Info

ItemTemplateInfo::ItemTemplateInfo()
    : TemplateInfo(), _class(0), _subClass(0), _unk0(0), _displayId(0), _quality(0), _flags(0), _buyCount(0),
    _buyPrice(0), _sellPrice(0), _inventoryType(0), _allowableClass(0), _allowableRace(0), _itemLevel(0),
    _requiredLevel(0), _requiredSkill(0), _requiredSkillRank(0), _requiredSpell(0), _requiredHonorRank(0),
    _requiredCityRank(0), _requiredReputationFaction(0), _requiredReputationRank(0), _maxCount(0), _stackable(0),
    _containerSlots(0), _armor(0), _holyRes(0), _fireRes(0), _natureRes(0), _frostRes(0), _shadowRes(0),
    _arcaneRes(0), _delay(0), _ammoType(0), _rangedModRange(0), _bonding(0), _description(""), _pageText(0),
    _languageId(0), _pageMaterial(0), _startQuest(0), _lockId(0), _material(0), _sheath(0), _randomProperty(0),
    _randomSuffix(0), _block(0), _itemSet(0), _maxDurability(0),_area(0), _map(0), _bagFamily(0), _totemCategory(0),
    _socketBonus(0), _gemProperties(0), _requiredDisenchantSkill(0), _armorDamageModifier(0), _scriptName(""),
    _disenchantId(0), _foodType(0), _minMoneyLoot(0), _maxMoneyLoot(0), _duration(0)
{
    for (int i = 0; i < 3; ++i)
    {
        _socketColor[i] = 0;
        _socketContent[i] = 0;
    }

    for (int i = 0; i < 5; ++i)
    {
        _statType[i] = 0;
        _statValue[i] = 0;
        _dmgMin[i] = 0;
        _dmgMax[i] = 0;
        _dmgType[i] = 0;
        _spellId[i] = 0;
        _spellTrigger[i] = 0;
        _spellCharges[i] = 0;
        _spellPPMRate[i] = 0;
        _spellCooldown[i] = 0;
        _spellCategory[i] = 0;
        _spellCategoryCooldown[i] = 0;
    }

    for (int i = 5; i < 10; ++i)
    {
        _statType[i] = 0;
        _statValue[i] = 0;
    }
}

ItemTemplateInfo::ItemTemplateInfo(const ItemTemplateInfo & iti)
    : TemplateInfo(iti.GetEntry(), iti.GetName())
{
    _class = iti.GetClass();
    _subClass = iti.GetSubClass();
    _unk0 = iti.GetUnk0();
    _displayId = iti.GetDisplayId();
    _quality = iti.GetQuality();
    _flags = iti.GetFlags();
    _buyCount = iti.GetBuyCount();
    _buyPrice = iti.GetBuyPrice();
    _sellPrice = iti.GetSellPrice();
    _inventoryType = iti.GetInventoryType();
    _allowableClass = iti.GetAllowableClass();
    _allowableRace = iti.GetAllowableRace();
    _itemLevel = iti.GetItemLevel();
    _requiredLevel = iti.GetRequiredLevel();
    _requiredSkill = iti.GetRequiredSkill();
    _requiredSkillRank = iti.GetRequiredSkillRank();
    _requiredSpell = iti.GetRequiredSpell();
    _requiredHonorRank = iti.GetRequiredHonorRank();
    _requiredCityRank = iti.GetRequiredCityRank();
    _requiredReputationFaction = iti.GetRequiredReputationFaction();
    _requiredReputationRank = iti.GetRequiredReputationRank();
    _maxCount = iti.GetMaxCount();
    _stackable = iti.GetStackable();
    _containerSlots = iti.GetContainerSlots();
    _armor = iti.GetArmor();
    _holyRes = iti.GetHolyRes();
    _fireRes = iti.GetFireRes();
    _natureRes = iti.GetNatureRes();
    _frostRes = iti.GetFrostRes();
    _shadowRes = iti.GetShadowRes();
    _arcaneRes = iti.GetArcaneRes();
    _delay = iti.GetDelay();
    _ammoType = iti.GetAmmoType();
    _rangedModRange = iti.GetRangedModRange();
    _bonding = iti.GetBonding();
    _description = iti.GetDescription();
    _pageText = iti.GetPageText();
    _languageId = iti.GetLanguageId();
    _pageMaterial = iti.GetPageMaterial();
    _startQuest = iti.GetStartQuest();
    _lockId = iti.GetLockId();
    _material = iti.GetMaterial();
    _sheath = iti.GetSheath();
    _randomProperty = iti.GetRandomProperty();
    _randomSuffix = iti.GetRandomSuffix();
    _block = iti.GetBlock();
    _itemSet = iti.GetItemSet();
    _maxDurability = iti.GetMaxDurability();
    _area = iti.GetArea();
    _map = iti.GetMap();
    _bagFamily = iti.GetBagFamily();
    _totemCategory = iti.GetTotemCategory();
    _socketBonus = iti.GetSocketBonus();
    _gemProperties = iti.GetGemProperties();
    _requiredDisenchantSkill = iti.GetRequiredDisenchantSkill();
    _armorDamageModifier = iti.GetArmorDamageModifier();
    _scriptName = iti.GetScriptName();
    _disenchantId = iti.GetDisenchantId();
    _foodType = iti.GetFoodType();
    _minMoneyLoot = iti.GetMinMoneyLoot();
    _maxMoneyLoot = iti.GetMaxMoneyLoot();
    _duration = iti.GetDuration();

    for (int i = 0; i < 3; ++i)
    {
        _socketColor[i] = iti.GetSocketColor(i);
        _socketContent[i] = iti.GetSocketContent(i);
    }

    for (int i = 0; i < 5; ++i)
    {
        _statType[i] = iti.GetStatType(i);
        _statValue[i] = iti.GetStatValue(i);
        _dmgMin[i] = iti.GetDmgMin(i);
        _dmgMax[i] = iti.GetDmgMax(i);
        _dmgType[i] = iti.GetDmgType(i);
        _spellId[i] = iti.GetSpellId(i);
        _spellTrigger[i] = iti.GetSpellTrigger(i);
        _spellCharges[i] = iti.GetSpellCharges(i);
        _spellPPMRate[i] = iti.GetSpellPPMRate(i);
        _spellCooldown[i] = iti.GetSpellCooldown(i);
        _spellCategory[i] = iti.GetSpellCategory(i);
        _spellCategoryCooldown[i] = iti.GetSpellCategoryCooldown(i);
    }

    for (int i = 5; i < 10; ++i)
    {
        _statType[i] = iti.GetStatType(i);
        _statValue[i] = iti.GetStatValue(i);
    }
}

Wt::WContainerWidget * ItemTemplateInfo::CreateContainer() const
{
    return NULL;
}

