#include "../preamble.h"
#include "SaturationRewriter.hpp"

namespace qbf2asp
{
  using logic::IQbfInstance;
  using logic::IQbfClause;
  using logic::variable_t;

  using std::ostream;
  using std::endl;
  using std::unordered_set;

  std::unordered_set<logic::variable_t> e_0_variables(const IQbfInstance & instance);
  std::unordered_set<logic::variable_t> a_1_variables(const IQbfInstance & instance);
  std::unordered_set<logic::variable_t> e_2_variables(const IQbfInstance & instance);
  
  void print_guess_rule(ostream & out);
  void print_facts(ostream & out, const IQbfInstance & instance);
  void print_clause_facts(ostream & out, const IQbfClause & clause, int clause_id);
  void print_saturation_rules(ostream & out, const IQbfInstance & instance);
  void print_main_rule(ostream & out, const IQbfInstance & instance);
  void print_constraint(ostream & out);
  bool clauses_are_uniform(const IQbfInstance & instance);
  int max_clause_length(const IQbfInstance & instance);

  SaturationRewriter::SaturationRewriter() { }

  SaturationRewriter::~SaturationRewriter() { }

  void SaturationRewriter::rewrite(
				   const IQbfInstance &instance) const
  {
    rewrite(instance, std::cout);
  }

  void SaturationRewriter::rewrite(
				   const IQbfInstance &instance,
				   ostream &out) const
  {
    if (instance.isDnf()) {
      std::cerr << "Disjunctive QBF not supported at the moment" << endl;
      exit(4);
    }
    if (instance.innermostQuantifierLevel() > 1) {
      std::cerr << "Only two quantifier levels are supported" << endl;
      exit(4);
    }
    if (!clauses_are_uniform(instance)) {
      std::cerr << "Only uniform clause instances supported at the moment" << endl;
      exit(4);
    }
    
    print_guess_rule(out);
    print_saturation_rules(out, instance);
    print_main_rule(out, instance);
    print_constraint(out);
    print_facts(out, instance);
  }

  bool clauses_are_uniform(const IQbfInstance & instance)
  {
    int first = 1;
    int clause_length = -1;
    for (auto & c : instance) {
      if (first) {
	clause_length = std::distance(c.begin(), c.end());
	first = false;
      } else {
	if (clause_length != std::distance(c.begin(), c.end())) {
	  return false;
	}
      }
    }
    return true;
  }

  int max_clause_length(const IQbfInstance & instance)
  {
    int max_length = 0;
    for (auto & c : instance) {
      int clause_length = std::distance(c.begin(),c.end());
	max_length = (clause_length < max_length) ? max_length : clause_length;
    }
    return max_length;
  }

  void print_constraint(ostream & out)
  {
    out << ":-" << " " << "not" << " " << "sat" << "." << endl;
  }
  
  void print_main_rule(ostream & out, const IQbfInstance & instance)
  {
    int positions = max_clause_length(instance);
    out << "sat" << " :-";
    for (int p = 0; p < positions; p++) {
      out << (p != 0 ? "," : "");
      out << " ";
      out << "pos" << "_" << p << "("
	  << "C" << "," << "X" << "_" << p << "," << "A" << "_" << p
	  << ")";
    }
    for (int p = 0; p < positions; p++) {
      out << "," << " ";
      out << "ass" << "(" << "X" << "_" << p << ","
	  << 1 << "-" << "A" << "_" << p << ")";
    }
    out << "." << endl;
  }

  void print_saturation_rules(ostream & out, const IQbfInstance & instance)
  {
    out << "ass" << "(" << "X" << "," << 0 << ")" << " :- "
	<< "sat" << "," << " " << "exists" << "(" << "X" << ")"
	<< "." << endl;
    out << "ass" << "(" << "X" << "," << 1 << ")" << " :- "
	<< "sat" << "," << " " << "exists" << "(" << "X" << ")"
	<< "." << endl;
  }
  
  void print_guess_rule(ostream & out)
  {
    out << "ass" << "(" << "X" << "," << 1 << ")" << " | "
	<< "ass" << "(" << "X" << "," << 0 << ")" << " :- "
	<< "var" << "(" << "X" << ")" << "." << endl;
  }
  
  void print_facts(ostream & out, const IQbfInstance & instance)
  {
    unordered_set<variable_t> a_1_vars = a_1_variables(instance);
    unordered_set<variable_t> e_0_vars = e_0_variables(instance);
    unordered_set<variable_t> variables = unordered_set<variable_t>();
    
    variables.insert(a_1_vars.begin(), a_1_vars.end());
    variables.insert(e_0_vars.begin(), e_0_vars.end());
    
    for (auto & x : variables) {
      out << "var" << "(" << "x" << "_" << x << ")" << "." << endl;
    }

    for (auto & x : e_0_vars) {
      out << "exists" << "(" << "x" << "_" << x << ")" << "." << endl;
    }

    for (IQbfInstance::const_iterator itc = instance.begin(); itc != instance.end(); ++itc) {
      int clause_id = std::distance(instance.begin(), itc);
      print_clause_facts(out, *itc, clause_id);
    }
  }

  void print_clause_facts(ostream & out, const IQbfClause & clause, int clause_id)
  {
    int position = 0;
    for (auto & v : clause) {
      out << "pos" << "_" << position << "(" << "c" << "_" << clause_id << ","
	  << "x" << "_" << v << ",";
      if (clause.isNegated(v)) {
	out << "0";
      } else {
	out << "1";
      }
      out << ")" << "." << endl;
      position++;
    }
  }

} // namespace qbf2asp
