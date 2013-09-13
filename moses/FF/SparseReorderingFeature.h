#pragma once

#include <string>

#include <boost/unordered_set.hpp>

#include <util/string_piece.hh>

#include "StatelessFeatureFunction.h"
#include "FFState.h"

namespace Moses
{

class SparseReorderingFeature : public StatelessFeatureFunction
{
public:
  enum Type {
    SourceCombined,
    SourceLeft,
    SourceRight
  };

	SparseReorderingFeature(const std::string &line);

	bool IsUseable(const FactorMask &mask) const
		{ return true; }

  void SetParameter(const std::string& key, const std::string& value);

	void Evaluate(const Phrase &source
	                        , const TargetPhrase &targetPhrase
	                        , ScoreComponentCollection &scoreBreakdown
	                        , ScoreComponentCollection &estimatedFutureScore) const
	{}
	void Evaluate(const InputType &input
	                        , const InputPath &inputPath
	                        , ScoreComponentCollection &scoreBreakdown) const
	{}

  virtual void Evaluate(const Hypothesis& hypo,
                        ScoreComponentCollection* accumulator) const
  {}
  void EvaluateChart(const ChartHypothesis &hypo,
                             ScoreComponentCollection* accumulator) const;


private:

  typedef boost::unordered_set<const Factor*> Vocab;

  void AddNonTerminalPairFeatures(
    const Sentence& sentence, const WordsRange& nt1, const WordsRange& nt2,
      bool isMonotone, ScoreComponentCollection* accumulator) const;

  void LoadVocabulary(const std::string& filename, Vocab& vocab);
  const Factor*  GetFactor(const Word& word, const Vocab& vocab, FactorType factor) const;

  Type m_type;
  FactorType m_sourceFactor;
  FactorType m_targetFactor;
  std::string m_sourceVocabFile;
  std::string m_targetVocabFile;

  const Factor* m_otherFactor;
  
  Vocab m_sourceVocab;
  Vocab m_targetVocab;

};


}

