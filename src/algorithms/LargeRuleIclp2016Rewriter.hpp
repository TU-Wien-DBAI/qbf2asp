#ifndef QBF2ASP_QBF2ASP_LARGERULEICLP2017REWRITER_H_
#define QBF1ASP_QBF2ASP_LARGERULEICLP2017REWRITER_H_

#include <qbf2asp/global>

#include <qbf2asp/IQbf2AspRewriter.hpp>

namespace qbf2asp
{

  /* This class implements the ICLP-2016 encoding for 2-QBFs and 3-QBFs. */
  class QBF2ASP_LOCAL LargeRuleIclp2016Rewriter : public IQbf2AspRewriter
  {
  protected:
    LargeRuleIclp2016Rewriter &operator=(LargeRuleIclp2016Rewriter &)
      { return *this; }

  public:
    LargeRuleIclp2016Rewriter();
    virtual ~LargeRuleIclp2016Rewriter() override;

    /* Generates the 2(3)-QBF encoding.
     * The generated encoding is written to stdout.
     * @param instance The 2(3)-QBF instance for which the encoding is
     * generated.
     */
    virtual void rewrite(
			 const logic::IQbfInstance &instance) const override;

    /* Generates the 2(3)-QBF encoding.
     * @param instance The 2(3)-QBF instance which is to be encoded.
     * @param out The generated encoding is written to this output stream.
     */
    virtual void rewrite(
			 const logic::IQbfInstance &instance,
			 std::ostream &out) const override;

  private:

    /* Computes the variables that occur in a given clause.
     * @param clause The clause.
     * @param variables The variables.
     * @return A list of variables containing the subset of the given variables
     * which occur in the clause.
     */
    const std::vector<logic::variable_t> clause_variables(
      const logic::IQbfClause & clause,
      const std::unordered_set<logic::variable_t> variables) const;

    /* Computes a clause's dual tuple.
     * @param clause The clause whose dual tuple is computed.
     * @param vars A list of all existentially quantified variables that
     * occur in the given clause.
     */
    std::vector<bool> dual_tuple(
      const logic::IQbfClause & clause,
      const std::vector<logic::variable_t> vars) const;

    /* Adds one to the given bitvector.
     * @param list The bitvector.
     * @param position The current position in the bitvector.
     * @return The carry of the addition of one to the given vector.
     */
    bool plus_one(std::vector<bool> & list, unsigned int position) const;

    /* Prints a bitvector as a comma separated list of 1's and 0's.
     * @param out The output stream to which the list is printed.
     * @param vector The bitvector.
     */
    void print_tuple(std::ostream &out, const std::vector<bool> & vector) const;

    /* Prints the guess rule (ICLP-1).
     * @param out The output stream to which the rule is printed.
     * @param instance The QBF instance for which the rule is generated.
     */
    void print_guess(
      std::ostream & out, const logic::IQbfInstance & instance) const;

    /* Prints the facts for a clause (ICLP-4).
     * @param out The output stream to be used for printing.
     * @param clause The clause for which the facts are generated
     * @param clause_id The identifier associated with the clause.
     */
    void print_clause_facts(
      std::ostream & out,
      const logic::IQbfClause & clause, int clause_id) const;

    /* Prints the rules (ICLP-2) and (ICLP-3) for a clause.
     * @param out The output stream to be used for printing.
     * @param clause The clause for which the rules are generated.
     * @param clause_id The identifier associated with the clause.
     */
    void print_clause_rules(
      std::ostream & out,
      const logic::IQbfClause & clause, int clause_id) const;

    /* Prints the rule (ICLP-4).
     * @param out The output stream to be used for printing.
     * @param instance The QBF instance for which the rule is generated.
     * @param qbf3sat Indicates whether the 3-QBF version of the rule is
     * to be printed (bottom is replaced by sat atom).
     */
    void print_constraint(
      std::ostream & out,
      const logic::IQbfInstance & instance, bool qbf3sat) const;

    /* Prints the saturation rules for the 3-QBF encoding.
     * @param out The output stream to be used for printing.
     * @param instance The 3-QBF instance for which the rules are generated.
     */
    void print_saturation_rules(
      std::ostream & out, const logic::IQbfInstance & instance) const;

    /* Prints the saturation constraint ( :- sat) for the 3-QBF encoding.
     * @param out The output stream to print the encoding to.
     */
    void print_saturation_constraint(std::ostream & out) const;

    /* Prints the eta tuple of a given clause.
     * @param out The output stream to print the tuple to.
     * @param clause The clause whose eta tuple is to be printed.
     */
    void print_eta_tuple(
      std::ostream & out, const logic::IQbfClause & clause) const;

  }; // class LargeRuleIclp2016Rewriter

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_LARGERULEICLP2017REWRITER_H_
