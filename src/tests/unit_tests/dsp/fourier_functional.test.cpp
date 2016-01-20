#include <boost/test/unit_test.hpp>

#ifdef BUILD_WITH_BOOST_THREAD

#include <boost/thread.hpp>

#include <k52/common/constants.h>
#include <k52/dsp/transform/i_fourier_transform.h>
#include <k52/dsp/transform/fast_fourier_transform.h>
#include <k52/parallel/i_worker_pool.h>
#include <k52/parallel/worker_pool_factory.h>

using std::vector;
using std::complex;
using k52::common::Constants;
using k52::parallel::ITask;
using k52::parallel::ITaskResult;
using k52::parallel::IWorkerPool;
using k52::parallel::WorkerPoolFactory;
using k52::dsp::IFourierTransform;
using k52::dsp::FastFourierTransform;


void complex_harmonic_transform(const IFourierTransform* ft)
{
    //Prepare
    size_t N = 128;
    size_t k0 = 5;

    vector< complex <double> > samples(N);

    for (size_t n = 0; n < N; ++n)
    {
        samples[n] = exp( 2 * Constants::Pi *
                          Constants::ImaginaryUnit * (double)k0 * (double)n / (double)N);
    }

    //Test
    vector< complex <double> > result = ft->Transform(samples);
}

BOOST_AUTO_TEST_SUITE(fourier_transform_functional_tests);

void test_function ()
{
    //Prepare
    size_t N = 1000;
    FastFourierTransform fft(N);
    vector< complex <double> > samples(N);

    //Test
    vector< complex <double> > result = fft.Transform(samples);
}

BOOST_AUTO_TEST_CASE(multithread_test)
{
    boost::thread_group threads;

    for (int i = 0; i < 10; ++i)
    {
        threads.create_thread(&test_function);
    }

    threads.join_all();
}

class TestTaskResult : public ITaskResult
{
};

class TestTask : public ITask
{
public:
    ITaskResult* Perform() const
    {
        FastFourierTransform fft(128);
        complex_harmonic_transform(&fft);

        return new TestTaskResult();
    }
};

BOOST_AUTO_TEST_CASE(thread_worker_pool_test)
{
    //Prepare
    IWorkerPool::shared_ptr pool =
            WorkerPoolFactory::CreateWorkerPool(WorkerPoolFactory::kThreadWorkerPool);

    vector<ITask::shared_ptr> tasks;
    vector<const ITask*> tasks_pointers;
    for (int i = 0; i < 10; ++i)
    {
        tasks.push_back(ITask::shared_ptr(new TestTask()));
        tasks_pointers.push_back(tasks[i].get());
    }

    //Test
    pool->DoTasks(tasks_pointers);
}

BOOST_AUTO_TEST_SUITE_END();

#endif
