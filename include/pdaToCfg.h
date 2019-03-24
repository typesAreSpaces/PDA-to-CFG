#ifndef _PDA_TO_CFG_
#define _PDA_TO_CFG_
#define Iterator(element, collection)							\
  std::set<std::string>::iterator element = collection.begin();		\
  element != collection.end();									\
  ++element
#define In(element, collection)					\
  collection.find(element) != collection.end()
#define SHOW_SECOND_THIRD_RULE true
#define EPS                    "epsilon"
#define LATEX_OUTPUT           false

#include <iostream>
#include <set>
#include <utility>
#include <map>

typedef std::set<std::string>                          States;
typedef std::set<std::string>                          Alphabet;
typedef std::set<std::string>                          StackAlphabet;
typedef std::pair<std::string, std::string>            Rule;
typedef std::set<Rule>                                 Grammar;
typedef std::set<std::pair<std::string, std::string> > PowerSetStateSigmaEps;
typedef std::map<std::pair<std::string, std::pair<std::string, std::string> >,
  PowerSetStateSigmaEps>                     Transitions;

Grammar pda_to_cfg(States, Alphabet,
				   StackAlphabet, Transitions,
				   States);
std::ostream & operator << (std::ostream &, const Rule &);
std::ostream & operator << (std::ostream &, const Grammar &);
#endif
