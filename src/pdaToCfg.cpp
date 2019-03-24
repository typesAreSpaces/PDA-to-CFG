#include "pdaToCfg.h"

// Notes:
// The string EPS (macro) is used
// as the epsilon string
// You can change the boolean value of the
// macro SHOW_SECOND_THIRD_RULE to display or
// not the rules produced by the second
// and third step
Grammar pda_to_cfg(States Q, Alphabet Sigma,
				   StackAlphabet Gamma, Transitions delta,
				   States final_states){

  // We add q_accept to the set
  // of states in order to have only
  // one single final state
  States Q2 = Q;
  Q2.insert("q_{accept}");
  Alphabet SigmaEps = Sigma;
  SigmaEps.insert(EPS);
  // Additional transitions must be added
  // to make q_accept the only final state
  Transitions delta2 = delta;
  for(Iterator(state, final_states))
	delta2[std::make_pair(*state,
						  std::make_pair(EPS,
										 EPS))].insert(std::make_pair("q_{accept}",
																	  EPS));
  // We start with an empty set
  // of rules
  Grammar set_of_rules;
  PowerSetStateSigmaEps first_transition, last_transition;
  // First rule
  for(Iterator(p, Q2))
	for(Iterator(q, Q2))
	  for(Iterator(r, Q2))
		for(Iterator(s, Q2))
		  for(Iterator(u, Gamma))
			for(Iterator(a, SigmaEps))
			  for(Iterator(b, SigmaEps)){
				first_transition =
				  delta2[std::make_pair(*p, std::make_pair(*a, EPS))],
				  last_transition =
				  delta2[std::make_pair(*s, std::make_pair(*b, *u))];
				if(In(std::make_pair(*r, *u), first_transition)
				   && In(std::make_pair(*q, EPS), last_transition))
				  set_of_rules.insert(std::make_pair("A_{" + *p + *q + "}",
													 *a + " A_{" + *r + *s + "} " + *b));
			  }
	
  // Second rule
  if(SHOW_SECOND_THIRD_RULE){
	for(Iterator(p, Q2))
	  for(Iterator(q, Q2))
		for(Iterator(r, Q2))
		  set_of_rules.insert(std::make_pair("A_{" + *p + *q + "}",
											 "A_{" + *p + *r + "}A_{" + *r + *q + "}"));
  }
	
  // Third rule
  if(SHOW_SECOND_THIRD_RULE){
	for(Iterator(p, Q2))
	  set_of_rules.insert(std::make_pair("A_{" + *p + *p + "}",
										 EPS));
  }
	
  return set_of_rules;
}

std::ostream & operator << (std::ostream & os, const Rule & r){
  if(LATEX_OUTPUT)
	os << "\\item $" << r.first << " \\rightarrow " << r.second << "$";
  else
	os << r.first << " -> " << r.second;
  return os;
}

std::ostream & operator << (std::ostream & os, const Grammar & g){
  if(LATEX_OUTPUT)
	os << "\\begin{itemize}" << std::endl;
  for(Grammar::iterator it = g.begin(); it != g.end(); ++it)
	os << *it << std::endl;
  if(LATEX_OUTPUT)
	os << "\\end{itemize}" << std::endl;
  return os;
}
