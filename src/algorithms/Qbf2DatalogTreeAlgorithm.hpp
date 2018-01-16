#ifndef QBF2ASP_QBF2ASP_QBF2DATALOGTREEALGORITHM_H_
#define QBF1ASP_QBF2ASP_QBF2DATALOGTREEALGORITHM_H_

#include <qbf2asp/global>

#include "Qbf2DatalogTable.hpp"

#include <qbf2asp/IQbf2AspTreeAlgorithm.hpp>

#include <qbf2asp/IDependencyOrder.hpp>

#include <logic/parsers>
#include <sharp/main>
#include <htd/main.hpp>

#include <list>

namespace qbf2asp
{

	class QBF2ASP_LOCAL Qbf2DatalogTreeAlgorithm : public IQbf2AspTreeAlgorithm
	{
	protected:
		Qbf2DatalogTreeAlgorithm &operator=(Qbf2DatalogTreeAlgorithm &)
		{ return *this; }

	public:
		Qbf2DatalogTreeAlgorithm();
		virtual ~Qbf2DatalogTreeAlgorithm() override;

		virtual void setOutputStream(std::ostream &out) override;

		virtual std::vector<const htd::ILabelingFunction *>
			preprocessOperations() const override;

		virtual sharp::ITable *evaluateNode(
				htd::vertex_t node,
				const htd::ITreeDecomposition &decomposition,
				const sharp::INodeTableMap &tables,
				const sharp::IDecomposableInstance &instance) const override;

		virtual bool needAllTables() const override;

        virtual void setDependencyOrder(qbf2asp::IDependencyOrder & order);

	protected:
		sharp::ITable *evaluateNode(
				htd::vertex_t node,
				const htd::ITreeDecomposition &decomposition,
				const sharp::INodeTableMap &tables,
				const logic::IQbfInstance &instance) const;

		Qbf2DatalogTable *createTable(
				htd::vertex_t node,
				const htd::ITreeDecomposition &decomposition,
				const sharp::INodeTableMap &tables,
				const logic::IQbfInstance &instance) const;

		Qbf2DatalogTable *createLeafTable(
				htd::vertex_t node,
				const htd::ITreeDecomposition &decomposition,
				const logic::IQbfInstance &instance) const;

		Qbf2DatalogTable *createNodeTable(
				htd::vertex_t node,
				const htd::ITreeDecomposition &decomposition,
				const sharp::INodeTableMap &tables,
				const logic::IQbfInstance &instance) const;

		const Qbf2DatalogTable &table(
				htd::vertex_t node,
				const sharp::INodeTableMap &tables) const;

		std::unordered_set<logic::variable_t> variablesToForget(
				htd::vertex_t node,
				const htd::ITreeDecomposition &decomposition) const;

		std::unordered_set<logic::clause_t> clauses(
				htd::vertex_t node,
				const htd::ITreeDecomposition &decomposition,
				const logic::IQbfInstance &instance) const;

	private:
		void processChildTables(
				htd::vertex_t node,
				const logic::IQbfInstance &instance,
				const std::unordered_set<logic::variable_t> &current,
				const sharp::INodeTableMap &tables,
				short &currentQuantifier,
				std::unordered_set<logic::variable_t> &remaining,
                std::unordered_set<logic::variable_t> &eliminated,
				std::unordered_set<logic::variable_t> &forgotten,
				htd::ConstIterator<htd::vertex_t> begin,
				htd::ConstIterator<htd::vertex_t> end) const;

		void printMappingRule(
				htd::vertex_t node,
				const std::unordered_set<logic::variable_t> &current,
				const std::unordered_set<logic::variable_t> &forgotten,
				htd::vertex_t child,
				const std::unordered_set<logic::variable_t> &ccurrent,
				const std::unordered_set<logic::variable_t> &cforgotten) const;

		void printClauseRule(
				const logic::IQbfInstance &instance,
				htd::vertex_t node,
				const std::list<logic::variable_t> &order,
				logic::clause_t clause) const;

		void printOutputRule(
				htd::vertex_t node,
				long step,
				const std::unordered_set<logic::variable_t> &current,
				const std::unordered_set<logic::variable_t> &forgotten,
				const std::list<logic::variable_t> &order) const;

		void printRootRules(htd::vertex_t node) const;

        void intersectRemainingVariables(
            const sharp::INodeTableMap &tables,
            std::unordered_set<logic::variable_t> & remaining,
            htd::ConstCollection<htd::vertex_t> children) const ;

        void printSingleExistentialEliminationRule(
            htd::vertex_t node,
            logic::variable_t var,
            std::list<logic::variable_t> &order,
            long &step) const;

        void printSingleUniversalEliminationRule(
            htd::vertex_t node,
            logic::variable_t var,
            std::list<logic::variable_t> &order,
            long &step) const;

        void printEliminationRules(
            const logic::IQbfInstance & instance,
            htd::vertex_t node,
            const std::unordered_set<logic::variable_t> &projectOut,
            std::list<logic::variable_t> &order,
            long &step) const;
        
	private:
		mutable std::ostream *out_;
        qbf2asp::IDependencyOrder * order_;

	}; // class Qbf2DatalogTreeAlgorithm

} // namespace qbf2asp

#endif // QBF2ASP_QBF2ASP_QBF2DATALOGTREEALGORITHM_H_
