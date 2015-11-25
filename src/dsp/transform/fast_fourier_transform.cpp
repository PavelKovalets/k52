#include <k52/dsp/transform/fast_fourier_transform.h>
#include <stdexcept>

#ifdef BUILD_WITH_FFTW3

#include <fftw3.h>

#endif

using ::std::vector;
using ::std::complex;
using ::std::invalid_argument;
using ::std::runtime_error;

namespace k52
{
namespace dsp
{

#ifdef BUILD_WITH_FFTW3

//Using pImpl approach to hide fftw3 for outside use
class FastFourierTransform::FastFourierTransformImpl
{
public:
    FastFourierTransformImpl(size_t sequence_size)
        : sequence_size_(sequence_size)
    {
        if(sequence_size <= 0)
        {
            throw std::invalid_argument("sequence_size <= 0");
        }

        in_ = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * sequence_size_);
        out_ = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * sequence_size_);
        plan_ = fftw_plan_dft_1d(sequence_size_, in_, out_, FFTW_FORWARD, FFTW_PATIENT);
    }

    ~FastFourierTransformImpl()
    {
        fftw_destroy_plan(plan_);
        fftw_free(in_);
        fftw_free(out_);
    }

    std::vector< std::complex< double > > Transform(
            const std::vector< std::complex< double > > &sequence)
    {
        if(sequence_size_ != sequence.size())
        {
            throw std::invalid_argument(
                    "FastFourierTransform can transform only data of the same size as was specified on construction.");
        }

        for (size_t n = 0; n < sequence_size_; ++n)
        {
            in_[n][0] = sequence[n].real();
            in_[n][1] = sequence[n].imag();
        }

        //Actual computations
        fftw_execute(plan_);

        vector< complex< double > > result(sequence_size_);

        for (size_t n = 0; n < sequence_size_; ++n)
        {
            result[n].real( out_[n][0] );
            result[n].imag( out_[n][1] );
        }

        return result;
    }

private:
    size_t sequence_size_;

    fftw_complex* in_;
    fftw_complex* out_;
    fftw_plan plan_;
};

FastFourierTransform::FastFourierTransform(size_t sequence_size)
{
    fast_fourier_transform_impl_ = new FastFourierTransformImpl(sequence_size);
}

FastFourierTransform::~FastFourierTransform()
{
    delete fast_fourier_transform_impl_;
}

vector< complex< double > > FastFourierTransform::Transform(
        const vector< complex< double > > &sequence) const
{
    return fast_fourier_transform_impl_->Transform(sequence);
}

#else

class FastFourierTransform::FastFourierTransformImpl{};

FastFourierTransform::FastFourierTransform(size_t sequence_size){}

FastFourierTransform::~FastFourierTransform(){}

vector< complex< double > > FastFourierTransform::Transform(
        const vector< complex< double > > &sequence) const
{
    throw runtime_error("The k52 library must be compiled with fftw3 to use FastFourierTransform class");
}

#endif //BUILD_WITH_FFTW3

} // namespace dsp
} // namespace k52

