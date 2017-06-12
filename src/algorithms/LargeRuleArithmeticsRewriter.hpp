#ifndef QBF2ASP_QBF2ASP_LARGERULEARITHMETICSREWRITER_H_
#define QBF1ASP_QBF2ASP_LARGERULEARITHMETICSREWRITER_H_

#include <qbf2asp/global>

#include <qbf2asp/IQbf2AspRewriter.hpp>

namespace qbf2asp
{
  class QBF2ASP_LOCAL LargeRuleArithmeticsRewriter : public IQbf2AspRewriter
  {
  protected:
    LargeRuleArithmeticsRewriter &operator=(LargeRuleArithmeticsRewriter &)
      { return *this; }

  public:
    LargeRuleArithmeticsRewriter();
    virtual ~LargeRuleArithmeticsRewriter() override;

    virtual void rewrite(
			 const logic::IQbfInstance &instance) const override;

    virtual void rewrite(
			 const logic::IQbfInstance &instance,
			 std::ostream &out) const override;
  private:
    void print_facts(
      std::ostream & out, const logic::IQbfInstance & instance) const;

    void print_guess(std::ostream & out) const;

    void print_constraint(
      std::ostream & out, const logic::IQbfInstance & instance) const;

    void print_tau_expr(
      std::ostream & out, const logic::IQbfClause & clause) const;

    void print_lambda_expr(
      std::ostream & out, logic::variable_t variable, bool isNegated) const;

    void print_saturation_constraint(std::ostream & out) const;

    void print_saturation_rules(
      std::ostream & out, const logic::IQbfInstance & instance) const;



  }; // class LargeRuleArithmeticsRewriter

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_LARGERULEARITHMETICSREWRITER_H_
