/*
 * TargetPhrase.h
 *
 *  Created on: 26 Apr 2016
 *      Author: hieu
 */

#pragma once
#include <sstream>
#include "PhraseImplTemplate.h"
#include "System.h"
#include "Scores.h"

namespace Moses2
{

template<typename WORD>
class TargetPhrase: public PhraseImplTemplate<WORD>
{
public:
  const PhraseTable &pt;
  mutable void **ffData;
  SCORE *scoreProperties;

  TargetPhrase(MemPool &pool, const PhraseTable &pt, const System &system, size_t size)
  : PhraseImplTemplate<WORD>(pool, size)
  , pt(pt)
  , scoreProperties(NULL)
  {
    m_scores = new (pool.Allocate<Scores>()) Scores(system, pool,
      system.featureFunctions.GetNumScores());
  }

  Scores &GetScores()
  {  return *m_scores; }

  const Scores &GetScores() const
  {  return *m_scores; }

  SCORE GetFutureScore() const
  {  return m_scores->GetTotalScore() + m_estimatedScore; }

  void SetEstimatedScore(const SCORE &value)
  {  m_estimatedScore = value; }

  SCORE *GetScoresProperty(int propertyInd) const
  {    return scoreProperties ? scoreProperties + propertyInd : NULL; }

  virtual std::string Debug(const System &system) const
  {
    std::stringstream out;
    out << Phrase<WORD>::Debug(system);
    out << " SCORES:" << GetScores().Debug(system);

    return out.str();
  }

protected:
  Scores *m_scores;
  SCORE m_estimatedScore;
};

///////////////////////////////////////////////////////////////////////
template<typename TP>
struct CompareFutureScore
{
  bool operator()(const TP *a, const TP *b) const
  {
    return a->GetFutureScore() > b->GetFutureScore();
  }

  bool operator()(const TP &a, const TP &b) const
  {
    return a.GetFutureScore() > b.GetFutureScore();
  }
};

template<typename TP>
struct CompareSortScore
{
  bool operator()(const TP *a, const TP *b) const
  {
    SCORE scoreA = a->sortScore;
    SCORE scoreB = b->sortScore;

    return scoreA > scoreB;
  }

};

} /* namespace Moses2a */

