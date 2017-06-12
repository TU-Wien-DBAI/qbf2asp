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

    virtual void rewrite(
			 const logic::IQbfInstance &instance) const override;

    virtual void rewrite(
			 const logic::IQbfInstance &instance,
			 std::ostream &out) const override;
  private:
    void print_guess_rule(std::ostream & out) const;
    void print_facts(std::ostream & out, const logic::IQbfInstance & instance) const;
    void print_clause_facts(std::ostream & out, const logic::IQbfInstance & instance, const logic::IQbfClause & clause, int clause_id) const;
    void print_saturation_rules(std::ostream & out) const;
    void print_main_rule(std::ostream & out, const logic::IQbfInstance & instance) const;
    void print_constraint(std::ostream & out) const;
    int max_clause_length(const logic::IQbfInstance & instance) const;


		
  }; // class SaturationRewriter

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_SATURATIONREWRITER_H_
