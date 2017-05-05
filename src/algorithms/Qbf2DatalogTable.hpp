#ifndef QBF2ASP_QBF2ASP_QBF2DATALOGTABLE_H_
#define QBF2ASP_QBF2ASP_QBF2DATALOGTABLE_H_

#include <qbf2asp/global>

#include <logic/parsers>

#include <sharp/main>

#include <htd/main.hpp>

#include <vector>
#include <unordered_set>

namespace qbf2asp
{

	class QBF2ASP_LOCAL Qbf2DatalogTable : public sharp::ITable
	{
	protected:
		Qbf2DatalogTable &operator=(Qbf2DatalogTable &) { return *this; }

	public:
		Qbf2DatalogTable();
		virtual ~Qbf2DatalogTable() override;

		std::vector<logic::variable_t> current;
		short outermostQuantifierLevel;
		std::unordered_set<logic::variable_t> remainingOutermost;

	}; // class Qbf2DatalogTable

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_QBF2DATALOGTABLE_H_
