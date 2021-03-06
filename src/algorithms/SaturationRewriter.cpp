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

  std::unordered_set<logic::variable_t> e_0_variables(
    const IQbfInstance & instance);

  std::unordered_set<logic::variable_t> a_1_variables(
    const IQbfInstance & instance);

  std::unordered_set<logic::variable_t> e_2_variables(
    const IQbfInstance & instance);

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

    print_guess_rule(out);
    print_saturation_rules(out);
    print_main_rule(out, instance);
    print_constraint(out);
    print_facts(out, instance);
  }

  int SaturationRewriter::max_clause_length(const IQbfInstance & instance) const
  {
    int max_length = 0;
    for (auto & c : instance) {
      int clause_length = std::distance(c.begin(),c.end());
	    max_length = (clause_length < max_length) ? max_length : clause_length;
    }
    return max_length;
  }

  void SaturationRewriter::print_constraint(ostream & out) const
  {
    out << ":-" << " " << "not" << " " << "sat" << "." << endl;
  }

  void SaturationRewriter::print_main_rule(
    ostream & out, const IQbfInstance & instance) const
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

  void SaturationRewriter::print_saturation_rules(ostream & out) const
  {
    out << "ass" << "(" << "X" << "," << 0 << ")" << " :- "
    << "sat" << "," << " " << "exists" << "(" << "X" << ")"
    << "." << endl;
    out << "ass" << "(" << "X" << "," << 1 << ")" << " :- "
    << "sat" << "," << " " << "exists" << "(" << "X" << ")"
    << "." << endl;
  }

  void SaturationRewriter::print_guess_rule(ostream & out) const
  {
    out << "ass" << "(" << "X" << "," << 1 << ")" << " | "
    << "ass" << "(" << "X" << "," << 0 << ")" << " :- "
    << "var" << "(" << "X" << ")" << "." << endl;
  }

  void SaturationRewriter::print_facts(
    ostream & out, const IQbfInstance & instance) const
  {
    unordered_set<variable_t> a_1_vars = a_1_variables(instance);
    unordered_set<variable_t> e_0_vars = e_0_variables(instance);
    unordered_set<variable_t> variables = unordered_set<variable_t>();

    variables.insert(a_1_vars.begin(), a_1_vars.end());
    variables.insert(e_0_vars.begin(), e_0_vars.end());

    out << "ass" << "(" << "f" << "," << 0 << ")" << "." << endl;

    for (auto & x : variables) {
      out << "var" << "(" << "x" << "_" << x << ")" << "." << endl;
    }

    for (auto & x : e_0_vars) {
      out << "exists" << "(" << "x" << "_" << x << ")" << "." << endl;
    }

    for (IQbfInstance::const_iterator itc = instance.begin();
      itc != instance.end(); ++itc) {
      int clause_id = std::distance(instance.begin(), itc);
      print_clause_facts(out, instance, *itc, clause_id);
    }
  }

  void SaturationRewriter::print_clause_facts(
    ostream & out,
    const IQbfInstance & instance,
    const IQbfClause & clause, int clause_id) const
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
    int max_position = max_clause_length(instance);
    for (; position < max_position; position++) {
      out << "pos" << "_" << position << "(" << "c" << "_" << clause_id << ","
      << "f" << "," << 1 << ")" << "." << endl;
    }
  }

} // namespace qbf2asp
