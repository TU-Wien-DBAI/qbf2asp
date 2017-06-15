#ifndef QBF2ASP_QBF2ASP_SATURATIONREWRITER_H_
#define QBF1ASP_QBF2ASP_SATURATIONREWRITER_H_

#include <qbf2asp/global>

#include <qbf2asp/IQbf2AspRewriter.hpp>

namespace qbf2asp
{

  class QBF2ASP_LOCAL SaturationRewriter : public IQbf2AspRewriter
  {
  protected:
    SaturationRewriter &operator=(SaturationRewriter &) { return *this; }

  public:
    SaturationRewriter();
    virtual ~SaturationRewriter() override;

    /* Prints the Saturation 2-QBF encoding to stdout.
     * @param instance The 2-QBF instance for which the encoding is generated.
     */
    virtual void rewrite(
			 const logic::IQbfInstance &instance) const override;

    /* Generates the Saturation 2-QBF encoding.
     * @param instance The instance for which the encoding is generated.
     * @param out The output stream to which the encoding is printed.
     */
    virtual void rewrite(
			 const logic::IQbfInstance &instance,
			 std::ostream &out) const override;
  private:
    /* Prints the guess rule (SAT-1).
     * @param out The output stream to which the rule is printed.
     */
    void print_guess_rule(std::ostream & out) const;

    /* Prints the facts for a given instance.
     * @param out The output stream to which the facts are printed.
     * @param instance The instance for which the facts are generated.
     */
    void print_facts(
      std::ostream & out, const logic::IQbfInstance & instance) const;

    /* Prints facts of the form pos_l(c_i, v, a_l).
     * @param out The output stream to which the facts are printed.
     * @param instance The instance for which the facts are generated.
     * @param clause The clause for which the facts are generated.
     * @param clause_id The identifier associated with the given clause.
     */
    void print_clause_facts(
      std::ostream & out,
      const logic::IQbfInstance & instance,
      const logic::IQbfClause & clause,
      int clause_id) const;

    /* Prints the saturation rules (SAT-2) and (SAT-3).
     * @param out The output stream to which the rules are printed.
     */
    void print_saturation_rules(std::ostream & out) const;

    /* Prints the rule (SAT-4) for a given instance.
     * @param out The output stream to which the rule is to be printed.
     * @param instance The instance for which the rule is generated.
     */
    void print_main_rule(
      std::ostream & out, const logic::IQbfInstance & instance) const;

    /* Prints the constraint (SAT-5).
     * @param out The output stream to which the rule is printed.
     */
    void print_constraint(std::ostream & out) const;

    /* Computes the maximum length of the clauses of a given instance.
     * @param instance The instance.
     */
    int max_clause_length(const logic::IQbfInstance & instance) const;

  }; // class SaturationRewriter

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_SATURATIONREWRITER_H_
