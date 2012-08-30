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

        template<class Action>
        void persist(Action& a)
        {
            Wt::Dbo::id(a, _entry, "entry");
            Wt::Dbo::field(a, _name, "name");
        }

        const long & GetEntry() const { return _entry; }
        const std::string & GetName() const { return _name; }

    private:
        long _entry;
        std::string _name;

};

typedef Wt::Dbo::collection<Wt::Dbo::ptr<TemplateInfo> > SearchResults;

// disable default version and id fields for SearchResult class
namespace Wt
{
    namespace Dbo
    {
        template<>
        struct dbo_traits<TemplateInfo> : public dbo_default_traits
        {
            static long invalidId()
            {
                return 0;
            }

            static const char *surrogateIdField()
            {
                return NULL;
            }

            static const char *versionField()
            {
                return NULL;
            }
        };
    }
}

#endif // H_DboClasses
