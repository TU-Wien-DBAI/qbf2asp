#ifndef QBF2ASP_QBF2ASP_LARGERULEARITHMETICSREWRITER_H_
#define QBF2ASP_QBF2ASP_LARGERULEARITHMETICSREWRITER_H_

#include <qbf2asp/global>

#include <qbf2asp/IQbf2AspRewriter.hpp>

namespace qbf2asp
{
    /**
     * @brief An QBF to ASP rewriter.
     * The rewriting implemented by this rewriter uses basic
     * arithmetic functions to simulate clauses.
     */
  class QBF2ASP_LOCAL LargeRuleArithmeticsRewriter : public IQbf2AspRewriter
  {
  protected:
    LargeRuleArithmeticsRewriter &operator=(LargeRuleArithmeticsRewriter &)
      { return *this; }

  public:
    LargeRuleArithmeticsRewriter();
    virtual ~LargeRuleArithmeticsRewriter() override;

    /**
     * @brief Generates the 2(3)-QBF encoding.
     * The generated encoding is written to stdout.
     * @param instance The 2(3)-QBF instance for which the encoding is
     * generated.
     */
    virtual void rewrite(
			 const logic::IQbfInstance &instance) const override;

     /** 
      * @brief Generates the 2(3)-QBF encoding.
      * @param instance The 2(3)-QBF instance which is to be encoded.
      * @param out The generated encoding is written to this output stream.
      */
    virtual void rewrite(
			 const logic::IQbfInstance &instance,
			 std::ostream &out) const override;
  private:

    /**
     * @brief Prints the facts (ARITH-1) and (ARITH-2).
     * @param out The output stream to which the facts are printed.
     * @param instance The QBF for which the facts are generated.
     */
    void print_facts(
      std::ostream & out, const logic::IQbfInstance & instance) const;

    /**
     * @brief Prints the guess rule (ARITH-3).
     * @param out The output stream to which the rule is printed.
     */
    void print_guess(std::ostream & out) const;

    /**
     * @brief Prints the constraint rule (ARITH-4).
     * @param out The output stream to which the rule is printed.
     * @param instance The QBF instance for which the rule is generated.
     */
    void print_constraint(
      std::ostream & out, const logic::IQbfInstance & instance) const;

    /**
     * @brief Prints the disjuntive expression for a given clause.
     * @param out The output stream to which the expression is printed to.
     * @param clause The clause for which the OR expression is generated.
     */
    void print_tau_expr(
      std::ostream & out, const logic::IQbfClause & clause) const;

    /**
     * @brief Prints the polarity expression for a given variable occurrence.
     * @param out The output stream to which the expression is printed to.
     * @param variable The variable for which the polarity expression is
     * printed.
     * @param isNegated Indicates whether the variable occurrence has negative
     * polarity.
     */
    void print_lambda_expr(
      std::ostream & out, logic::variable_t variable, bool isNegated) const;

    /**
     * @brief Prints the saturation constraint for the 3-QBF encoding.
     * @param out The output stream to which the constraint is printed to.
     */
    void print_saturation_constraint(std::ostream & out) const;

    /**
     * @brief Prints the saturation rules for the 3-QBF encoding.
     * @param out The output stream to which the rules are printed to.
     * @param instance The 3-QBF instance for which the rules are generated.
     */
    void print_saturation_rules(
      std::ostream & out, const logic::IQbfInstance & instance) const;

  }; // class LargeRuleArithmeticsRewriter

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_LARGERULEARITHMETICSREWRITER_H_
