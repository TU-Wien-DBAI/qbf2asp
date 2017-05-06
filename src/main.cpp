#include "preamble.h"

#include <qbf2asp/main>
#include <logic/parsers>
#include <sharp/main>
#include <htd/main.hpp>

#include <memory>
#include <fstream>

#include <cstdlib>
#include <cstring>
#include <csignal>

#ifdef HAVE_UNISTD_H 
	#include <unistd.h>
#else
//FIXME: what if we don't have unistd.h for getopt?
#endif

namespace
{
	const int EXIT_ARGUMENT_ERROR = 1;
	const int EXIT_FILEOPEN_ERROR = 2;
	const int EXIT_PARSING_ERROR = 3;

	struct Qbf2AspOptions
	{
		enum DecompositionHeuristic
		{
			MINIMUM_FILL_EDGES = 0,
			MAXIMUM_CARDINALITY_SEARCH
		};

		Qbf2AspOptions(int argc, char *argv[])
		{
			int opt;
			long alg;
#ifdef ENABLE_DECOMPOSITION
			while((opt = getopt(argc, argv, "vhbds:a:t:")) != -1)
#else // !defined(ENABLE_DECOMPOSITION)
			while((opt = getopt(argc, argv, "vhbs:a:")) != -1)
#endif // ENABLE_DECOMPOSITION
				switch(opt)
				{
				case 'v':
					this->displayVersion = true;
					break;

				case 'h':
					this->displayHelp = true;
					break;

#ifdef ENABLE_DECOMPOSITION
				case 'd':
					this->decompositionOnly = true;
					break;

				case 't':
					this->customTreeDecomposition = true;
					if(!std::strcmp(optarg, "mf"))
						this->heuristic = MINIMUM_FILL_EDGES;
					else if(!std::strcmp(optarg, "mcs"))
						this->heuristic = MAXIMUM_CARDINALITY_SEARCH;
					else
						this->error = true;
					break;
#endif // ENABLE_DECOMPOSITION

				case 'b':
					if(this->printBenchmarks)
						this->printMachineReadable = true;
					this->printBenchmarks = true;
					break;

				case 's':
					this->useSeed = true;
					this->seed = (unsigned)strtol(optarg, NULL, 10);
					break;

				case 'a':
					this->customRewriter = true;
					alg = strtol(optarg, NULL, 10);
					if(alg >= 0 && alg < qbf2asp::create::INVALID_MAXIMUM)
						this->rewriter = (qbf2asp::create::Rewriter)alg;
					else
						this->error = true;
					break;

				default:
					this->error = true;
					break;
				}

			if(optind + 1 == argc)
			{
				this->readFromFile = true;
				this->fileToRead = argv[optind];
			}
			else if(optind != argc) this->error = true;
		}

		bool error = false;
		bool displayVersion = false; // -v, --version
		bool displayHelp = false; // -h, --help
		bool printBenchmarks = false; // -b, --benchmark
		bool printMachineReadable = false; // 2x -b, --benchmark
		bool decompositionOnly = false; // -d, --decomp
		bool customTreeDecomposition = false; // -t, --tree
		DecompositionHeuristic heuristic = MINIMUM_FILL_EDGES;
		bool useSeed = false; // -s, --seed
		unsigned seed = 0;
		bool readFromFile = false;
		char *fileToRead = nullptr;
		bool customRewriter = false; // -c <config>, --config=<config>
		qbf2asp::create::Rewriter rewriter = qbf2asp::create::SATURATION;
	};

	void
	printHelp(const char *programName)
	{
		std::cerr
			<< "Usage: " << programName << " [OPTION]... [FILE]"
				<< std::endl
			<< "Rewrite QBF formulas to answer set programs."
				<< std::endl
			<< std::endl
			<< "Arguments to options are always mandatory. Valid options:"
				<< std::endl
			<< "  -v\t  output version information and exit" << std::endl
			<< "  -h\t  display this help message and exit" << std::endl
#ifdef ENABLE_DECOMPOSITION
			<< "  -d\t  perform decomposition and print treewidth" << std::endl
			<< "  -t ALG  use ALG for decomposition, where ALG is one of:"
				<< std::endl
			<< "\t    mcs: maximum cardinality search bucket elimination"
				<< std::endl
			<< "\t    mf:  minimum fill edge count bucket elimination (default)"
				<< std::endl
#endif // ENABLE_DECOMPOSITION
			<< "  -b\t  display timing information (use twice for CSV format)"
				<< std::endl
			<< "  -s NUM  set NUM as seed for the random number generator"
				<< std::endl
			<< "  -a NUM  set rewriter to NUM:" << std::endl
			<< "\t    " << qbf2asp::create::SATURATION
				<< ": rewrite to ASP via saturation encoding (default)"
				<< std::endl
			<< "\t    " << qbf2asp::create::LARGE_RULE_ICLP2016
				<< ": rewrite to ASP via ICLP'16 large rule encoding"
				<< std::endl
			<< "\t    " << qbf2asp::create::LARGE_RULE_ARITHMETICS
				<< ": rewrite to ASP via large rule arithmetics encoding"
				<< std::endl
#ifdef ENABLE_DECOMPOSITION
			<< "\t    " << qbf2asp::create::DATALOG_VIA_DECOMPOSITION
				<< ": rewrite to Datalog via tree decomposition"
				<< std::endl
#endif // ENABLE_DECOMPOSITION
			<< std::endl
			<< "Exit status: " << std::endl
			<< " " << EXIT_SUCCESS << "  if OK," << std::endl
			<< " " << EXIT_ARGUMENT_ERROR << "  if problems parsing options"
				<< std::endl
			<< " " << EXIT_FILEOPEN_ERROR << "  if problems opening input file"
				<< std::endl
			<< " " << EXIT_PARSING_ERROR << "  if problems parsing input"
				<< std::endl
			<< std::endl
			<< "Report qbf2asp bugs to " << PACKAGE_BUGREPORT << std::endl;
	}

	void
	printVersion()
	{
		std::cerr
			<< PACKAGE_STRING << std::endl
			<< "Copyright (C) 2017 Jannik Vierling" << std::endl
			<< "License GPLv3+: GNU GPL version 3 or later "
				<< "<http://gnu.org/licenses/gpl.html>." << std::endl
			<< "This is free software: you are free to change and "
				<< "redistribute it." << std::endl
			<< "There is NO WARRANTY, to the extent permitted by law."
				<< std::endl
			<< std::endl
			<< "Written by Michael Morak." << std::endl;
	}

	void printBenchmarks(int signal)
	{
		std::cerr << std::endl;
		logic::Benchmark::printBenchmarks(std::cerr, false);

		exit(signal);
	}

	void printBenchmarksMachineReadable(int signal)
	{
		std::cerr << std::endl;
		logic::Benchmark::printBenchmarks(std::cerr, true);

		exit(signal);
	}
}

int main(int argc, char *argv[])
{
	logic::Benchmark::registerTimestamp("program start");

	const Qbf2AspOptions opts(argc, argv);

	if(opts.error)
	{
		printHelp(argv[0]);
		exit(EXIT_ARGUMENT_ERROR);
	}

	if(opts.displayHelp)
	{
		printHelp(argv[0]);
		exit(EXIT_SUCCESS);
	}

	if(opts.displayVersion)
	{
		printVersion();
		exit(EXIT_SUCCESS);
	}

	if(opts.printBenchmarks && opts.printMachineReadable)
	{
		signal(SIGABRT, printBenchmarksMachineReadable);
		signal(SIGFPE, printBenchmarksMachineReadable);
		signal(SIGILL, printBenchmarksMachineReadable);
		signal(SIGINT, printBenchmarksMachineReadable);
		signal(SIGSEGV, printBenchmarksMachineReadable);
		signal(SIGTERM, printBenchmarksMachineReadable);
	}
	else if(opts.printBenchmarks)
	{
		signal(SIGABRT, printBenchmarks);
		signal(SIGFPE, printBenchmarks);
		signal(SIGILL, printBenchmarks);
		signal(SIGINT, printBenchmarks);
		signal(SIGSEGV, printBenchmarks);
		signal(SIGTERM, printBenchmarks);
	}

	if(opts.useSeed)
	{
		std::srand(opts.seed);
	}

#ifdef ENABLE_DECOMPOSITION
	if(opts.customTreeDecomposition)
	{
		std::unique_ptr<htd::LibraryInstance> htdlib(
				htd::createManagementInstance(htd::Id::FIRST));

		htd::IOrderingAlgorithm *ct = nullptr;

		switch(opts.heuristic)
		{
		case Qbf2AspOptions::MAXIMUM_CARDINALITY_SEARCH:
			ct = new htd::MaximumCardinalitySearchOrderingAlgorithm(
					&qbf2asp::create::htdlib());
			break;

		case Qbf2AspOptions::MINIMUM_FILL_EDGES:
		default:
			ct = new htd::MinFillOrderingAlgorithm(&qbf2asp::create::htdlib());
			break;
		}

		htdlib->orderingAlgorithmFactory().setConstructionTemplate(ct);
		qbf2asp::create::set(htdlib.release());
	}
#endif // ENABLE_DECOMPOSITION

	std::ifstream inputFileStream;
	std::istream *inputStream = &std::cin;
	if(opts.readFromFile)
	{
		inputStream = &inputFileStream;
		inputFileStream.open(opts.fileToRead, std::ifstream::in);

		if(inputFileStream.fail() || !inputFileStream.is_open())
		{
			std::cerr
				<< "Failed to read from file '" << opts.fileToRead << "'."
				<< std::endl;

			exit(EXIT_FILEOPEN_ERROR);
		}
	}

	std::cerr << "Parsing..." << std::endl;
	std::unique_ptr<logic::IQDIMACSParser> parser(
			logic::parser::qdimacsParser());
	std::unique_ptr<logic::IQbfInstance> instance(
			parser->parse(inputStream));
	parser.reset();
	logic::Benchmark::registerTimestamp("parsing time");

	if(!instance.get())
		exit(EXIT_PARSING_ERROR);

	std::cerr << "Initializing rewriter..." << std::endl;
	std::unique_ptr<qbf2asp::IQbf2AspRewriter> rewriter(
			qbf2asp::create::rewriter(opts.rewriter));

#ifdef ENABLE_DECOMPOSITION
	// check to see if we have a tree decomposition rewriter
	if(opts.rewriter == qbf2asp::create::DATALOG_VIA_DECOMPOSITION)
	{
		qbf2asp::IQbf2AspTreeRewriter &treeRewriter(
				static_cast<qbf2asp::IQbf2AspTreeRewriter &>(*rewriter.get()));

		std::cerr << "Decomposing..." << std::endl;

		qbf2asp::DecomposableQbfInstance decomposableInstance(*instance);
		std::unique_ptr<htd::ITreeDecomposition> decomposition(
				treeRewriter.decompose(decomposableInstance));

		std::cerr << "TREEWIDTH: "
			<< decomposition->maximumBagSize() - 1
			<< std::endl;

		if(!opts.decompositionOnly)
		{
			std::cerr << "Rewriting... " << std::flush;
			sharp::ISolution *solution = treeRewriter.solve(
					decomposableInstance,
					*decomposition);
			std::cerr << "done." << std:: endl;

			if(solution) delete solution;
		}
	}
	else // non-tree-decomposition-based rewriter
	{
#endif

		std::cerr << "Rewriting... " << std::flush;
		rewriter->rewrite(*instance);
		std::cerr << "done." << std::endl;
		
#ifdef ENABLE_DECOMPOSITION
	}
#endif

	if(opts.printBenchmarks)
	{
		std::cerr << std::endl;
		logic::Benchmark::printBenchmarks(std::cerr, opts.printMachineReadable);
	}

	return EXIT_SUCCESS;
}
