#include "../preamble.h"
#include "LargeRuleArithmeticsRewriter.hpp"

namespace qbf2asp
{
  using logic::IQbfInstance;
  using logic::variable_t;
  using logic::IQbfClause;

  using std::ostream;
  using std::endl;
  using std::unordered_set;

  const std::unordered_set<logic::variable_t> a_1_variables(
    const logic::IQbfInstance & instance);
  const std::unordered_set<logic::variable_t> x_variables(
    const logic::IQbfInstance & instance);
  const std::unordered_set<logic::variable_t> y_variables(
    const logic::IQbfInstance & instance);

  LargeRuleArithmeticsRewriter::LargeRuleArithmeticsRewriter() { }

  LargeRuleArithmeticsRewriter::~LargeRuleArithmeticsRewriter() { }

  void LargeRuleArithmeticsRewriter::rewrite(const IQbfInstance &instance) const
  {
    rewrite(instance, std::cout);
  }

  void LargeRuleArithmeticsRewriter::rewrite(
    const IQbfInstance &instance, ostream &out) const
  {
    if (instance.isDnf()) {
      std::cerr << "Disjunctive QBF not supported at the moment" << endl;
      exit(4);
    }
    if (instance.innermostQuantifierLevel() > 2) {
      std::cerr << "Only three quantifier levels are supported" << endl;
      exit(4);
    }
    print_facts(out, instance);
    print_guess(out);
    print_constraint(out, instance);

    if(instance.innermostQuantifierLevel() == 2) {
      print_saturation_constraint(out);
      print_saturation_rules(out, instance);
    }
  }

  void LargeRuleArithmeticsRewriter::print_saturation_constraint(
    ostream & out) const
  {
    out << ":-" << " " << "not" << " " << "sat" << "." << endl;
  }

  void LargeRuleArithmeticsRewriter::print_saturation_rules(
    ostream & out, const IQbfInstance & instance) const
  {
    const unordered_set<variable_t> & forall_1_variables
    = a_1_variables(instance);

    for (auto & x : forall_1_variables) {
      out << "assign" << "(" << "x" << "_" << x << ", " << "1" << ")" << " "
	  << ":-" << " " << "sat" << "." << endl;
      out << "assign" << "(" << "x" << "_" << x << ", " << "0" << ")" << " "
	  << ":-" << " " << "sat" << "." << endl;
    }
  }

  void LargeRuleArithmeticsRewriter::print_constraint(
    ostream & out, const IQbfInstance & instance) const
  {
    bool first = true;
    const unordered_set<variable_t> x_vars = x_variables(instance);
    const unordered_set<variable_t> y_vars = y_variables(instance);

    if (instance.innermostQuantifierLevel() == 2) {
      out << "sat" << " " << ":-";
    } else {
      out << ":-";
    }

    for (auto & x : x_vars) {
      out << (first ? " " : ", ") << "assign" << "(" << "x" << "_" << x << ", "
      << "V" << "_" << x << ")";
      first = false;
    }
    for (auto & y : y_vars) {
      out << (first ? " " : ", ") << "tf" << "(" << "V" << "_" << y << ")";
      first = false;
    }
    int clause_id = 0;
    for (IQbfInstance::const_iterator itc = instance.begin();
      itc != instance.end(); ++itc) {
      if (clause_id == 0) {
	       out << (first ? " " : ", ") << "N" << "_" << clause_id << " = ";
	       out << "(";
         print_tau_expr(out, *itc);
         out << ")";
         first = false;
       } else {
         out << ", " << "N" << "_" << clause_id << " = " << "(" << "N" << "_"
         << (clause_id - 1) << " & ";
         out << "(";
         print_tau_expr(out, *itc);
         out << ")" << ")";
       }
       clause_id++;
     }
     if (clause_id > 0) {
       out << ", " << "N" << "_" << (clause_id - 1) << " = " << "1";
    }
    out << "." << endl;
  }

  void LargeRuleArithmeticsRewriter::print_tau_expr(
    ostream & out, const IQbfClause & clause) const
  {
    bool first = true;
    for (auto & x : clause) {
      if (!first) {
        out << " " << "?" << " ";
      }
      print_lambda_expr(out, x, clause.isNegated(x));
      first = false;
    }
  }

  void LargeRuleArithmeticsRewriter::print_lambda_expr(
    ostream & out, variable_t variable, bool isNegated) const
  {
    if (isNegated) {
      out << "(" << "1" << "-" << "V" << "_" << variable << ")";
    } else {
      out << "V" << "_" << variable;
    }
  }

  void LargeRuleArithmeticsRewriter::print_facts(
    ostream & out, const IQbfInstance & instance) const
  {
    const unordered_set<variable_t> x_vars = x_variables(instance);
    out << "tf" << "(" << "0" << ")" << "." << endl;
    out << "tf" << "(" << "1" << ")" << "." << endl;
    for (auto & x : x_vars) {
      out << "forall"<< "(" << "x" << "_" << x << ")" << "." << endl;
    }
  }

  void LargeRuleArithmeticsRewriter::print_guess(ostream & out) const
  {
    out << "assign" << "(" << "X" << ", " << "1" << ")" << " " << "|" << " "
	<< "assign" << "(" << "X" << ", " << "0" << ")" << " "
	<< ":-" << " " << "forall" << "(" << "X" << ")" << "." << endl;
  }

} // namespace qbf2asp
