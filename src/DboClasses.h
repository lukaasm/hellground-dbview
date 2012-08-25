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
    SEARCH_CREATURE     = 0,
    SEARCH_GAMEOBJECT   = 1,
    SEARCH_QUEST        = 2,
    SEARCH_SPELL        = 3,
    SEARCH_ITEM         = 4
};

static const char * SearcherTableNames [5] =
{
    "creature_template",
    "gameobject_template",
    "quest_template",
    "spell_info",
    "item_template"
};

struct SearchResult
{
    long entry;
    std::string name;

    template<class Action>
    void persist(Action& a)
    {
        Wt::Dbo::id(a, entry, "entry");
        Wt::Dbo::field(a, name, "name");
    }
};

typedef Wt::Dbo::collection<Wt::Dbo::ptr<SearchResult> > SearchResults;

// disable default version and id fields for SearchResult class
namespace Wt
{
    namespace Dbo
    {
        template<>
        struct dbo_traits<SearchResult> : public dbo_default_traits
        {
            static long invalidId()
            {
                return long(0);
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
