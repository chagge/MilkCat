//
// The MIT License (MIT)
//
// Copyright 2013-2014 The MilkCat Project Developers
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// multiclass_perceptron.h --- Created at 2014-10-10
//

#ifndef SRC_ML_MULTICLASS_PERCEPTRON_H_
#define SRC_ML_MULTICLASS_PERCEPTRON_H_

#include <vector>

namespace milkcat {

class FeatureSet;
class PerceptronModel;
template<class T> class PackedScore;

// A averaged perceptron for multiclass classification
class Perceptron {
 public:
  Perceptron(PerceptronModel *model);
  virtual ~Perceptron();

  // Classify the given feature_set, returns the inferenced label id (yid).
  // Use `yname` to get the string of this label. 
  int Classify(const FeatureSet *feature_set);

  // Get the name of a label (yid) or get yid by name
  const char *yname(int yid) const;
  int ysize() const;
  float ycost(int yid) const { return ycost_[yid]; }

  // Online training the perceptron with one sample. Returns true if the weights
  // have not been updated (prediction is correct), else, returns false. 
  bool Train(const FeatureSet *feature_set, const char *label);

  // Update and add `value` for `yid` of `feature_set`
  void Update(const FeatureSet *feature_set, int yid, float value);

  // Increases the sample count for average training. It should be called when
  // a sample is trained. Otherwise, it behaviors just like a normal perceptron
  void IncreaseSampleCount();

  // Finish the training of averaged perceptron. Average each weights from cached
  // score
  void FinishTrain();

 private:
  PerceptronModel *model_;
  float *ycost_;
  std::vector<PackedScore<float> *> cached_score_;
  int sample_count_;

  // Updates the cached average score. It is called by `Update`
  void UpdateCachedScore(int xid, int yid, float value);
};

}  // namespace milkcat

#endif
