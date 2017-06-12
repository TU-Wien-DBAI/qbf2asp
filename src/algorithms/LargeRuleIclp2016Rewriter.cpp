#include "../preamble.h"
#include "LargeRuleIclp2016Rewriter.hpp"

#include <vector>

namespace qbf2asp
{
  using logic::IQbfInstance;
  using logic::IQbfClause;
  using logic::variable_t;

  using std::ostream;
  using std::endl;
  using std::unordered_set;
  using std::vector;

  LargeRuleIclp2016Rewriter::LargeRuleIclp2016Rewriter() { }

  LargeRuleIclp2016Rewriter::~LargeRuleIclp2016Rewriter() { }

  void LargeRuleIclp2016Rewriter::rewrite(const IQbfInstance &instance) const
  {
    rewrite(instance, std::cout);
  }

  std::unordered_set<logic::variable_t> e_0_variables(
    const IQbfInstance & instance);

  std::unordered_set<logic::variable_t> a_1_variables(
    const IQbfInstance & instance);

  std::unordered_set<logic::variable_t> e_2_variables(
    const IQbfInstance & instance);

  const unordered_set<variable_t> x_variables(const IQbfInstance & instance);
  const unordered_set<variable_t> y_variables(const IQbfInstance & instance);

  static const char * ASP_BOT = "";
  static const char * ASP_VAR_Y = "Y";
  static const char * ASP_PRED_C = "c";
  static const char * ASP_PRED_T = "t";
  static const char * ASP_PRED_F = "f";
  static const char * ASP_TERM_X = "x";
  static const char * ASP_PRED_SAT = "sat";
  static const char * ASP_NOT      = "not";
  static const char * ASP_RULE_SYM = ":-";

  void LargeRuleIclp2016Rewriter::rewrite(
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

    print_guess(out, instance);

    for (IQbfInstance::const_iterator itc = instance.begin();
    itc != instance.end(); ++itc) {
      int clause_id = std::distance(instance.begin(), itc);
      print_clause_rules(out, *itc, clause_id);
      print_clause_facts(out, *itc, clause_id);
    }

    print_constraint(out, instance, instance.innermostQuantifierLevel() == 2);

    if (instance.innermostQuantifierLevel() == 2) {
      print_saturation_constraint(out);
      print_saturation_rules(out, instance);
    }
  }

  void LargeRuleIclp2016Rewriter::print_saturation_rules(
    ostream & out, const IQbfInstance & instance) const
  {
    const std::unordered_set<logic::variable_t> & forall_1_variables
    = a_1_variables(instance);

    for (auto it = forall_1_variables.begin();
    it != forall_1_variables.end(); ++it) {
      out << ASP_PRED_T << "(" << ASP_TERM_X << "_" << *it << ")"
	  << " " << ASP_RULE_SYM << " " << ASP_PRED_SAT << "." << endl;
      out << ASP_PRED_F << "(" << ASP_TERM_X << "_" << *it << ")"
	  << " " << ASP_RULE_SYM << " " << ASP_PRED_SAT << "." << endl;
    }
    for (IQbfInstance::const_iterator itc = instance.begin();
    itc != instance.end(); ++itc) {
      int clause_id = std::distance(instance.begin(), itc);
      vector<variable_t> clause_y
      = clause_variables(*itc, e_0_variables(instance));
      std::vector<bool> tuple = std::vector<bool>(clause_y.size());
      do {
        out << ASP_PRED_C << "_" << clause_id;
        if (clause_y.size() > 0) {
          out << "(";
          print_tuple(out, tuple);
          out << ")";
        }
        out << " " << ASP_RULE_SYM << " " << ASP_PRED_SAT << "." << endl;
      } while (!plus_one(tuple, 0));
    }
  }

  void LargeRuleIclp2016Rewriter::print_saturation_constraint(
    ostream & out) const
  {
    out << ASP_BOT << " " << ASP_RULE_SYM << " " << ASP_NOT << " "
    << ASP_PRED_SAT << "." << endl;
  }

  void LargeRuleIclp2016Rewriter::print_clause_rules(
    ostream & out, const IQbfClause & clause, int clause_id) const
  {
    std::vector<logic::variable_t> clause_x
    = clause_variables(clause, x_variables(clause.instance()));
    std::vector<logic::variable_t> clause_y
    = clause_variables(clause, e_0_variables(clause.instance()));
    for (auto it = clause_x.begin(); it != clause_x.end(); ++it) {
      const char * polarity = !clause.isNegated(*it) ? "t" : "f";
      out << "c" << "_" << clause_id;
      if (clause_y.size() > 0) {
        out << "(";
        print_tuple(out, dual_tuple(clause, clause_y));
        out << ")";
      }
      out << " :- " << polarity << "(x_" << *it << ")." << endl;
    }
  }

  void LargeRuleIclp2016Rewriter::print_clause_facts(
    ostream & out, const IQbfClause & clause, int clause_id) const
  {
    std::vector<logic::variable_t> clause_y
    = clause_variables(clause, e_0_variables(clause.instance()));
    std::vector<bool> tuple = std::vector<bool>(clause_y.size());
    std::vector<bool> dual  = dual_tuple(clause, clause_y);
    do {
      if (tuple != dual) {
        out << "c_" << clause_id << "(";
        print_tuple(out, tuple);
        out << ")." << endl;
      }
    } while (!plus_one(tuple, 0));
  }

  void LargeRuleIclp2016Rewriter::print_guess(
    ostream & out, const IQbfInstance & instance) const
  {
    const std::unordered_set<logic::variable_t> x_vars = x_variables(instance);

    for (auto it = x_vars.begin(); it != x_vars.end(); ++it) {
      out << "t(x_" << *it << ") | f(x_" << *it << ")." << endl;
    }
  }

  void LargeRuleIclp2016Rewriter::print_eta_tuple(
    ostream & out, const IQbfClause & clause) const
  {
    std::vector<logic::variable_t> clause_y_vars
    = clause_variables(clause, e_0_variables(clause.instance()));
    for (unsigned int i = 0; i < clause_y_vars.size(); i++) {
      out << (i != 0 ? "," : "") << ASP_VAR_Y << "_" << clause_y_vars.at(i);
    }
  }

  void LargeRuleIclp2016Rewriter::print_constraint(
    ostream & out, const IQbfInstance & instance, bool qbf3sat) const
  {
    bool first = true;
    out << (qbf3sat ? ASP_PRED_SAT : ASP_BOT) << " :- ";
    for (IQbfInstance::const_iterator itc = instance.begin();
    itc != instance.end(); ++itc) {
      int clause_id = std::distance(instance.begin(), itc);
      vector<variable_t> clause_y
      = clause_variables(*itc, e_0_variables(instance));
      out << (first ? "" : ", ");
      out << "c_" << clause_id;
      if (clause_y.size() > 0) {
        out << "(";
        print_eta_tuple(out, *itc);
        out << ")";
      }
      first = false;
    }
    out << "." << endl;
  }

  void LargeRuleIclp2016Rewriter::print_tuple(
    ostream &out, const std::vector<bool> & vector) const
  {
    for (unsigned int i = 0; i < vector.size(); i++) {
      out << vector.at(i) << (i == vector.size() - 1 ? "" : ",");
    }
  }

  bool LargeRuleIclp2016Rewriter::plus_one(
    std::vector<bool> & list, unsigned int position) const
  {
    bool new_carry = false;
    if (list.empty()) {
      new_carry = true;
    } else if (list.size() - 1 == position) {
      if (list.at(position)) {
	list.at(position) = false;
	new_carry = true;
      } else {
	list.at(position) = true;
	new_carry = false;
      }
    } else {
      bool old_carry = plus_one(list, position + 1);
      new_carry = list.at(position) && old_carry;
      list.at(position) = list.at(position) != old_carry;
    }
    return new_carry;
  }

  const std::vector<logic::variable_t>
  LargeRuleIclp2016Rewriter::clause_variables(
    const IQbfClause & clause,
    const std::unordered_set<logic::variable_t> x_variables) const
  {
    std::vector<logic::variable_t> result = std::vector<logic::variable_t>();
    for (auto it = x_variables.begin(); it != x_variables.end(); ++it) {
      if (clause.contains(*it)) {
        result.push_back(*it);
      }
    }
    return result;
  }

  std::vector<bool> LargeRuleIclp2016Rewriter::dual_tuple(
    const IQbfClause & clause, const std::vector<logic::variable_t> vars) const
  {
    std::vector<bool> dual = std::vector<bool>(vars.size());
    for (unsigned int i = 0; i < vars.size(); i++) {
      dual.at(i) = clause.isNegated(vars.at(i)) ? true : false;
    }
    return dual;
  }

  std::unordered_set<logic::variable_t> e_0_variables(
    const IQbfInstance & instance)
  {
    return instance.variables(instance.innermostQuantifierLevel());
  }

  std::unordered_set<logic::variable_t> a_1_variables(
    const IQbfInstance & instance)
  {
    return instance.innermostQuantifierLevel() - 1 >= 0
      ? instance.variables(instance.innermostQuantifierLevel() - 1)
      : std::unordered_set<logic::variable_t>();
  }

  std::unordered_set<logic::variable_t> e_2_variables(
    const IQbfInstance & instance)
  {
    return instance.innermostQuantifierLevel() - 2 >= 0
      ? instance.variables(instance.innermostQuantifierLevel() - 2)
      : std::unordered_set<logic::variable_t>();
  }

  const unordered_set<variable_t> x_variables(const IQbfInstance & instance)
  {
    const unordered_set<variable_t> a_vars = a_1_variables(instance);
    unordered_set<variable_t> x_vars
    = unordered_set<variable_t>(e_2_variables(instance));
    x_vars.insert(a_vars.begin(), a_vars.end());
    return x_vars;
  }

  const unordered_set<variable_t> y_variables(const IQbfInstance & instance)
  {
    return unordered_set<variable_t>(e_0_variables(instance));
  }

} // namespace qbf2asp
