#ifndef QBF2ASP_QBF2ASP_LARGERULEICLP2017REWRITER_H_
#define QBF1ASP_QBF2ASP_LARGERULEICLP2017REWRITER_H_

#include <qbf2asp/global>

#include <qbf2asp/IQbf2AspRewriter.hpp>

namespace qbf2asp
{

  class QBF2ASP_LOCAL LargeRuleIclp2016Rewriter : public IQbf2AspRewriter
  {
  protected:
    LargeRuleIclp2016Rewriter &operator=(LargeRuleIclp2016Rewriter &)
      { return *this; }

  public:
    LargeRuleIclp2016Rewriter();
    virtual ~LargeRuleIclp2016Rewriter() override;

    virtual void rewrite(
			 const logic::IQbfInstance &instance) const override;

    virtual void rewrite(
			 const logic::IQbfInstance &instance,
			 std::ostream &out) const override;

  private:
    
    const std::vector<logic::variable_t>
      clause_variables(const logic::IQbfClause & clause,
		       const std::unordered_set<logic::variable_t> x_variables) const;
    std::vector<bool>
      dual_tuple(const logic::IQbfClause & clause, const std::vector<logic::variable_t> vars) const;

    bool plus_one(std::vector<bool> & list, unsigned int position) const;
    
    void print_tuple(std::ostream &out, const std::vector<bool> & vector) const;
    void print_guess(std::ostream & out, const logic::IQbfInstance & instance) const;
    void print_clause_facts(std::ostream & out, const logic::IQbfClause & clause, int clause_id) const;
    void print_clause_rules(std::ostream & out, const logic::IQbfClause & clause, int clause_id) const;
    void print_constraint(std::ostream & out, const logic::IQbfInstance & instance, bool qbf3sat) const;
    void print_saturation_rules(std::ostream & out, const logic::IQbfInstance & instance) const;
    void print_saturation_constraint(std::ostream & out) const;
    void print_eta_tuple(std::ostream & out, const logic::IQbfClause & clause) const;

  }; // class LargeRuleIclp2016Rewriter

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_LARGERULEICLP2017REWRITER_H_
