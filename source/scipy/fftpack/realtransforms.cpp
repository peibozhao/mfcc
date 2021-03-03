
#include "realtransforms.h"
#include "scipy/fft/_pocketfft/pocketfft_hdronly.h"
#include "scipy/fft/_pocketfft//helper.h"
namespace scipy {

static float norm_fct(int inorm, size_t N) {
  if (inorm==0) return float(1);
  if (inorm==2) return float(1/float(N));
  if (inorm==1) return float(1/std::sqrt(float(N)));
  throw std::invalid_argument("invalid value for inorm (must be 0, 1, or 2)");
}

static float norm_fct(int inorm, const pocketfft::shape_t &shape, const pocketfft::shape_t &axes, size_t fct = 1, int delta = 0) {
    if (inorm == 0) { return 1.f; }
    size_t N(1);
    for (auto a: axes) {
        N *= fct * size_t(int64_t(shape[a])+delta);
    }
    return norm_fct(inorm, N);
}

static std::vector<float> dct_internal(const std::vector<float> &in, int axis, int type, int inorm) {
    // TODO
    pocketfft::shape_t axes(1);
    axes[0] = 0;
    pocketfft::shape_t dims(1);
    dims[0] = in.size();
    std::vector<float> res(dims[0], 0.f);
    pocketfft::stride_t s_in(1);
    s_in[0] = sizeof(float);
    pocketfft::stride_t s_out(1);
    s_out[0] = sizeof(float);
    const float *d_in = in.data();

    float *d_out = res.data();

    float fct = (type == 1) ? norm_fct(inorm, dims, axes, 2, -1) : norm_fct(inorm, dims, axes, 2);
    bool ortho = inorm == 1;
    // std::cout << dims[0] << std::endl;
    // std::cout << s_in[0] << std::endl;
    // std::cout << axes[0] << std::endl;
    // std::cout << type << std::endl;
    // std::cout << d_in[0] << std::endl;
    // std::cout << d_in[1] << std::endl;
    // std::cout << d_in[2] << std::endl;
    // std::cout << fct << std::endl;
    // std::cout << ortho << std::endl;
    pocketfft::dct<float>(dims, s_in, s_out, axes, type, d_in, d_out, fct, ortho, 1);
    // std::cout << d_out[0] << std::endl;
    // std::cout << d_out[1] << std::endl;
    // std::cout << d_out[2] << std::endl;
    return res;
}

std::vector<float> dct(const std::vector<float> &x, int type, std::optional<int> n, int axis, const std::optional<std::string> &norm, bool overwrite_x) {
    // __r2r
    bool forward = true;
    int inorm = _normalization(norm, forward);
    if (!forward) {
        if (type == 2) {
            type = 3;
        } else if (type == 3) {
            type = 2;
        }
    }

    if (type < 1 || type > 4) {
        throw std::invalid_argument("invalid DCT type");
    }

    // dct
    return dct_internal(x, axis, type, inorm);
}

}

