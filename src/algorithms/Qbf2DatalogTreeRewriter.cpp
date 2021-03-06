#include "../preamble.h"
#include "Qbf2DatalogTreeRewriter.hpp"

#include <qbf2asp/create.hpp>
#include <qbf2asp/DecomposableQbfInstance.hpp>

#include <qbf2asp/IDependencyOrder.hpp>
#include "../DependencyOrder.hpp"

namespace qbf2asp
{
    using logic::IQbfInstance;

    using sharp::IDecomposableInstance;
    using sharp::ISolution;
		
    using htd::ITreeDecomposition;
    using htd::ITreeDecompositionAlgorithm;

    using std::unique_ptr;

    Qbf2DatalogTreeRewriter::Qbf2DatalogTreeRewriter()
	:	tdAlgorithm_(create::htdlib().treeDecompositionAlgorithmFactory()
                             .createInstance()),
		treeAlgorithm_(create::treeAlgorithm()),
		solver_(sharp::create::treeSolver(*tdAlgorithm_, *treeAlgorithm_))
    { }

    Qbf2DatalogTreeRewriter::~Qbf2DatalogTreeRewriter() { }

    void Qbf2DatalogTreeRewriter::rewrite(const IQbfInstance &instance) const
    {
        rewrite(instance, std::cout);
    }

    void Qbf2DatalogTreeRewriter::rewrite(
        const IQbfInstance &instance,
        std::ostream &out) const
    {
        treeAlgorithm_->setOutputStream(out);

        ISolution *solution = solve(DecomposableQbfInstance(instance));
        if(solution) delete solution;
    }

    ITreeDecomposition *Qbf2DatalogTreeRewriter::decompose(
        const IDecomposableInstance &instance) const
    {
        return solver_->decompose(instance);
    }

    ISolution *Qbf2DatalogTreeRewriter::solve(
        const IDecomposableInstance &instance) const
    {
        return solver_->solve(instance);
    }

    ISolution *Qbf2DatalogTreeRewriter::solve(
        const IDecomposableInstance &instance,
        const ITreeDecomposition &decomposition) const
    {
        const IQbfInstance & formula =
            static_cast<const DecomposableQbfInstance *>(&instance)->content();

        switch(m_scheme) {
        case 1 : {
            TrivialDependencyOrder order(formula);
            treeAlgorithm_->setDependencyOrder(order);
        }
            break;
        case 2 : {
            StandardDependencyOrder order(formula);
            treeAlgorithm_->setDependencyOrder(order);
        }
            break;
        default:
            throw "Invalid dependency scheme";
        }
        
        return solver_->solve(instance, decomposition);
    }

    void Qbf2DatalogTreeRewriter::setDependencyScheme(int scheme)
    {
        m_scheme = scheme;
    }

} // namespace qbf2asp
