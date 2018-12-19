#ifndef AI_TOOLBOX_BANDIT_MODEL_HEADER_FILE
#define AI_TOOLBOX_BANDIT_MODEL_HEADER_FILE

#include <AIToolbox/Types.hpp>
#include <AIToolbox/Utils/Core.hpp>

#include <memory>

namespace AIToolbox::Bandit {
    template <typename... Args>
    class Model {
        public:
            using Arms = std::tuple<Args...>;

            Model(Args... args) : args_(new Arms(std::move(args)...)) {}

            std::tuple<double> sampleR(size_t a) const {
                return tuple_get(*args_, a, [this](auto x) -> double {
                    return x(rand_);
                });
            }

            size_t getA() {
                return std::tuple_size_v<Arms>;
            }

            double getExpectedReward(size_t a) const {
                return a;
                // FIXME: Can't get mean for general distributions yet.
                // Maybe boost distributions?
                // return tuple_get(*args_, a, [this](auto x) -> int {
                //     return x.mean();
                // });
            }

        private:
            std::unique_ptr<Arms> args_;

            mutable RandomEngine rand_;
    };
}

#endif
