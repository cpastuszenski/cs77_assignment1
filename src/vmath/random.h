#ifndef _RANDOM_H_
#define _RANDOM_H_

#include "stdmath.h"
#include "vec.h"

#include <random>
#include <vector>

struct Rng {
    std::minstd_rand                        engine;
    
    void seed(unsigned int seed) { engine.seed(seed); }
	
	float next_float() { return std::uniform_real_distribution<float>(0,1)(engine); }
	float next_float(float a, float b) { return std::uniform_real_distribution<float>(a,b)(engine); }
	float next_float(const vec2f& v) { return next_float(v.x,v.y); }
	float next_float(const range1f& r) { return next_float(r.min,r.max); }
	
    vec2f next_vec2f() { return vec2f(next_float(),next_float()); }
    vec3f next_vec3f() { return vec3f(next_float(),next_float(),next_float()); }
    
	int next_int(int a, int b) { return std::uniform_int_distribution<int>(a,b)(engine); }
    int next_int(const vec2i& v) { return next_int(v.x,v.y); }
    int next_int(const range1i& r) { return next_int(r.min,r.max); }
};

inline std::vector<Rng*> rng_generate_seeded(int nrngs) {
    std::seed_seq sseq{0,1,2,3,4,5,6,7,8,9};
    auto seeds = std::vector<int>(nrngs);
    sseq.generate(seeds.begin(), seeds.end());
    auto rngs = std::vector<Rng*>(nrngs);
    for(int i = 0; i < nrngs; i ++) {
        rngs[i] = new Rng();
        rngs[i]->seed(seeds[i]);
    }
    return rngs;
}

#endif
