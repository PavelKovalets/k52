#include <boost/test/unit_test.hpp>

#ifdef BUILD_WITH_BOOST_THREAD

#include <k52/common/constants.h>
#include <k52/dsp/transform/i_fourier_transform.h>
#include <k52/dsp/transform/fast_fourier_transform.h>
#include <k52/parallel/i_worker_pool.h>
#include <k52/parallel/worker_pool_factory.h>

void complex_harmonic_transform(const k52::dsp::IFourierTransform* ft)
{
    //Prepare
    size_t N = 128;
    size_t k0 = 5;

    std::vector< std::complex <double> > samples(N);

    for (size_t n = 0; n < N; ++n)
    {
        samples[n] = exp( 2 * k52::common::Constants::Pi *
                          k52::common::Constants::ImaginaryUnit * (double)k0 * (double)n / (double)N);
    }

    //Test
    std::vector< std::complex <double> > result = ft->Transform(samples);
}

BOOST_AUTO_TEST_SUITE(fourier_transform_functional_tests);

class TestTaskResult : public k52::parallel::ITaskResult
{
};

class TestTask : public k52::parallel::ITask
{
public:
    k52::parallel::ITaskResult* Perform() const
    {
        k52::dsp::FastFourierTransform fft(128);
        complex_harmonic_transform(&fft);

        return new TestTaskResult();
    }
};

BOOST_AUTO_TEST_CASE(multithread_test)
{
    k52::parallel::IWorkerPool::shared_ptr pool =
            k52::parallel::WorkerPoolFactory::CreateWorkerPool(k52::parallel::WorkerPoolFactory::kThreadWorkerPool);

    std::vector<k52::parallel::ITask::shared_ptr> tasks;
    std::vector<const k52::parallel::ITask*> tasks_pointers;
    for (int i = 0; i < 10; ++i)
    {
        tasks.push_back(k52::parallel::ITask::shared_ptr(new TestTask()));
        tasks_pointers.push_back(tasks[i].get());
    }

    pool->DoTasks(tasks_pointers);
}

BOOST_AUTO_TEST_SUITE_END();

#endif
