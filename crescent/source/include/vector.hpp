#pragma once
#include <cmath>
#include <algorithm>

constexpr double pi = 3.1415926535897932384; // pi
constexpr double tau = pi * 2.;               // pi * 2
__forceinline constexpr float deg_to_rad(float val) {
	return val * ( float )((double)pi / 180.);
}

// radians to degrees.
__forceinline constexpr float rad_to_deg(float val) {
	return val * (float)(180. / (double)pi);
}

__forceinline float rad_n( float a ) noexcept {
	return std::isfinite( a ) ? std::remainder( a, ( float )tau ) : 0.f;
}

__forceinline float rad_d( float a, float b ) noexcept {
	auto d = rad_n( a - b );

	if ( a >  b ) {
		if ( d >= ( float )pi )
			d -= ( float )tau;
	}

	else if ( d <= -( float )pi )
		d += ( float )tau;

	return d;
}

struct rect_t {
	int x, y, w, h;
};

inline void SinCos(float radians, float* sine, float* cosine)
{
	_asm
	{
		fld		DWORD PTR[radians]
		fsincos

		mov edx, DWORD PTR[cosine]
		mov eax, DWORD PTR[sine]

		fstp DWORD PTR[edx]
		fstp DWORD PTR[eax]
	}
}

__inline void SinCos(const float& r, float& s, float& c)
{
	s = sin(r);
	c = cos(r);
}

// Remap a value in the range [A,B] to [C,D].
inline float RemapVal(float val, float A, float B, float C, float D)
{
	if (A == B)
		return val >= B ? D : C;
	return C + (D - C) * (val - A) / (B - A);
}

inline float RemapValClamped(float val, float A, float B, float C, float D)
{
	if (A == B)
		return val >= B ? D : C;
	float cVal = (val - A) / (B - A);
	cVal = std::clamp(cVal, 0.0f, 1.0f);

	return C + (D - C) * cVal;
}

__forceinline float remap( float val, float a, float b, float c, float d ) {
	return RemapValClamped( val, a, b, c, d );
}

using matrix3x4_t = float[3][4];

class vec4_t {
public:
	float x, y, z, h;
};

class vec2_t {
public:
	vec2_t( ) {
		x = y = 0.0f;
	}

	vec2_t( float X, float Y ) {
		x = X; y = Y;
	}

	vec2_t( float* v ) {
		x = v[ 0 ]; y = v[ 1 ];
	}

	vec2_t( const float* v ) {
		x = v[ 0 ]; y = v[ 1 ];
	}

	vec2_t( const vec2_t& v ) {
		x = v.x; y = v.y;
	}

	vec2_t& operator=( const vec2_t& v ) {
		x = v.x; y = v.y; return *this;
	}

	float& operator[]( int i ) {
		return ( ( float* )this )[ i ];
	}

	float operator[]( int i ) const {
		return ( ( float* )this )[ i ];
	}

	vec2_t& operator+=( const vec2_t& v ) {
		x += v.x; y += v.y; return *this;
	}

	vec2_t& operator-=( const vec2_t& v ) {
		x -= v.x; y -= v.y; return *this;
	}

	vec2_t& operator*=( const vec2_t& v ) {
		x *= v.x; y *= v.y; return *this;
	}

	vec2_t& operator/=( const vec2_t& v ) {
		x /= v.x; y /= v.y; return *this;
	}

	vec2_t& operator+=( float v ) {
		x += v; y += v; return *this;
	}

	vec2_t& operator-=( float v ) {
		x -= v; y -= v; return *this;
	}

	vec2_t& operator*=( float v ) {
		x *= v; y *= v; return *this;
	}

	vec2_t& operator/=( float v ) {
		x /= v; y /= v; return *this;
	}

	vec2_t operator+( const vec2_t& v ) const {
		return vec2_t( x + v.x, y + v.y );
	}

	vec2_t operator-( const vec2_t& v ) const {
		return vec2_t( x - v.x, y - v.y );
	}

	vec2_t operator*( const vec2_t& v ) const {
		return vec2_t( x * v.x, y * v.y );
	}

	vec2_t operator/( const vec2_t& v ) const {
		return vec2_t( x / v.x, y / v.y );
	}

	vec2_t operator+( float v ) const {
		return vec2_t( x + v, y + v );
	}

	vec2_t operator-( float v ) const {
		return vec2_t( x - v, y - v );
	}

	vec2_t operator*( float v ) const {
		return vec2_t( x * v, y * v );
	}

	vec2_t operator/( float v ) const {
		return vec2_t( x / v, y / v );
	}

	void set( float X = 0.0f, float Y = 0.0f ) {
		x = X; y = Y;
	}

	float length( void ) const {
		return sqrtf( x * x + y * y );
	}

	float length_sqr( void ) const {
		return ( x * x + y * y );
	}

	float dist_to( const vec2_t& v ) const {
		return ( *this - v ).length( );
	}

	float dist_to_sqr( const vec2_t& v ) const {
		return ( *this - v ).length_sqr( );
	}

	float dot( const vec2_t& v ) const {
		return ( x * v.x + y * v.y );
	}

	bool is_zero( void ) const {
		return ( x > -FLT_EPSILON && x < FLT_EPSILON &&
			y > -FLT_EPSILON && y < FLT_EPSILON );
	}

	operator bool( ) const noexcept {
		return !is_zero( );
	}

public:
	float x, y;
};

class vec3_t {
public:
	vec3_t( ) {
		x = y = z = 0.0f;
	}

	vec3_t( float X, float Y, float Z ) {
		x = X; y = Y; z = Z;
	}

	vec3_t( float* v ) {
		x = v[ 0 ]; y = v[ 1 ]; z = v[ 2 ];
	}

	vec3_t( const float* v ) {
		x = v[ 0 ]; y = v[ 1 ]; z = v[ 2 ];
	}

	vec3_t( const vec3_t& v ) {
		x = v.x; y = v.y; z = v.z;
	}

	vec3_t( const vec2_t& v ) {
		x = v.x; y = v.y; z = 0.0f;
	}

	__forceinline vec3_t& operator=( const vec3_t& v ) {
		x = v.x; y = v.y; z = v.z; return *this;
	}

	__forceinline vec3_t& operator=( const vec2_t& v ) {
		x = v.x; y = v.y; z = 0.0f; return *this;
	}

	float& operator[]( int i ) {
		return ( ( float* )this )[ i ];
	}

	__forceinline float operator[]( int i ) const {
		return ( ( float* )this )[ i ];
	}

	vec3_t& operator+=( const vec3_t& v ) {
		x += v.x; y += v.y; z += v.z; return *this;
	}

	vec3_t& operator-=( const vec3_t& v ) {
		x -= v.x; y -= v.y; z -= v.z; return *this;
	}

	vec3_t& operator*=( const vec3_t& v ) {
		x *= v.x; y *= v.y; z *= v.z; return *this;
	}

	vec3_t& operator/=( const vec3_t& v ) {
		x /= v.x; y /= v.y; z /= v.z; return *this;
	}

	vec3_t& operator+=( float v ) {
		x += v; y += v; z += v; return *this;
	}

	vec3_t& operator-=( float v ) {
		x -= v; y -= v; z -= v; return *this;
	}

	vec3_t& operator*=( float v ) {
		x *= v; y *= v; z *= v; return *this;
	}

	vec3_t& operator/=( float v ) {
		x /= v; y /= v; z /= v; return *this;
	}

	__forceinline vec3_t operator+( const vec3_t& v ) const {
		return vec3_t( x + v.x, y + v.y, z + v.z );
	}

	__forceinline vec3_t operator-( const vec3_t& v ) const {
		return vec3_t( x - v.x, y - v.y, z - v.z );
	}

	__forceinline vec3_t operator*( const vec3_t& v ) const {
		return vec3_t( x * v.x, y * v.y, z * v.z );
	}

	__forceinline vec3_t operator/( const vec3_t& v ) const {
		return vec3_t( x / v.x, y / v.y, z / v.z );
	}

	__forceinline vec3_t operator+( float v ) const {
		return vec3_t( x + v, y + v, z + v );
	}

	__forceinline vec3_t operator-( float v ) const {
		return vec3_t( x - v, y - v, z - v );
	}

	__forceinline vec3_t operator*( float v ) const {
		return vec3_t( x * v, y * v, z * v );
	}

	__forceinline vec3_t operator/( float v ) const {
		return vec3_t( x / v, y / v, z / v );
	}

	inline vec3_t to_vec( ) const {
		auto out = vec3_t( );
		float sp, sy, cp, cy;

		SinCos( deg_to_rad( x ), &sp, &cp );
		SinCos( deg_to_rad( y ), &sy, &cy );

		out.x = cp * cy;
		out.y = cp * sy;
		out.z = -sp;

		return out;
	}

	inline void angle_vectors(vec3_t* forward) const {
		float sp, sy, cp, cy;

		SinCos(deg_to_rad(x), &sp, &cp);
		SinCos(deg_to_rad(y), &sy, &cy);

		if (forward)
		{
			forward->x = cp * cy;
			forward->y = cp * sy;
			forward->z = -sp;
		}
	}

	inline vec3_t vel_to_ang( ) const {
		auto magnitude = [ & ]( const vec3_t& v ) -> float {
			return sqrtf( v.dot( v ) );
		};

		float yaw, pitch;

		if ( y == 0.f && x == 0.f ) {
			yaw = 0.0f;

			if ( z > 0.f )
				pitch = 270.f;

			else pitch = 90.f;
		}

		else {
			yaw = rad_to_deg( ::atan2f( y, x ) );
			pitch = rad_to_deg( ::atan2f( -z, magnitude( *this ) ) );

			if ( yaw < 0.f )
				yaw += 360.f;

			if ( pitch < 0.f )
				pitch += 360.f;
		}

		return { pitch, yaw, 0.f };
	}

	inline void angle_vectors(vec3_t* forward, vec3_t* right, vec3_t* up) const {
		float sr, sp, sy, cr, cp, cy;
		SinCos(deg_to_rad(x), &sp, &cp);
		SinCos(deg_to_rad(y), &sy, &cy);
		SinCos(deg_to_rad(z), &sr, &cr);

		if (forward)
		{
			forward->x = cp * cy;
			forward->y = cp * sy;
			forward->z = -sp;
		}

		if (right)
		{
			right->x = (-1 * sr * sp * cy + -1 * cr * -sy);
			right->y = (-1 * sr * sp * sy + -1 * cr * cy);
			right->z = -1 * sr * cp;
		}

		if (up)
		{
			up->x = (cr * sp * cy + -sr * -sy);
			up->y = (cr * sp * sy + -sr * cy);
			up->z = cr * cp;
		}
	}

	__forceinline float length( ) const {
		return sqrtf( x * x + y * y + z * z );
	}

	__forceinline float length_sqr( ) const {
		return ( x * x + y * y + z * z );
	}

	__forceinline float length_2d( ) const {
		return sqrtf( x * x + y * y );
	}

	__forceinline float length_2d_sqr( ) const {
		return ( x * x + y * y );
	}

	__forceinline float dist_to( const vec3_t& v ) const {
		return ( *this - v ).length( );
	}

	__forceinline float dist_to_sqr( const vec3_t& v ) const {
		return ( *this - v ).length_sqr( );
	}

	__forceinline float dot( const vec3_t& v ) const {
		return ( x * v.x + y * v.y + z * v.z );
	}

	__forceinline vec3_t look( vec3_t to ) const {
		to -= *this;
		vec3_t angles;
		if ( to.y == 0.0f && to.x == 0.0f ) {
			angles.x = ( to.z > 0.0f ) ? 270.0f : 90.0f;
			angles.y = 0.0f;
		}
		else {
			angles.x = rad_to_deg( ::atan2f( -to.z, to.length_2d( ) ) );
			angles.y = rad_to_deg( ::atan2f( to.y, to.x ) );
		}

		angles.z = 0.0f;
		return angles;
	}

	__forceinline float fov_to( vec3_t to ) {
		vec3_t v_src = vec3_t( );
		angle_vectors( &v_src );

		vec3_t v_dst = vec3_t( );
		to.angle_vectors( &v_dst );

		float result = rad_to_deg( ::acosf( v_dst.dot( v_src ) / v_dst.length_sqr( ) ) );

		if ( !::isfinite( result ) || ::isinf( result ) || ::isnan( result ) )
			result = 0.0f;

		return result;
	}

	vec3_t cross( const vec3_t& v ) const {
		return vec3_t( y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x );
	}

	bool is_zero( ) const {
		return ( x > -FLT_EPSILON && x < FLT_EPSILON &&
			y > -FLT_EPSILON && y < FLT_EPSILON &&
			z > -FLT_EPSILON && z < FLT_EPSILON );
	}

	operator bool( ) const {
		return !is_zero( );
	}

	inline void normalize_vector( ) {
		vec3_t& v = *this;

		float iradius = 1.f / ( length( ) + FLT_EPSILON ); //FLT_EPSILON

		v.x *= iradius;
		v.y *= iradius;
		v.z *= iradius;
	}

	vec3_t abs( ) const {
		return vec3_t{ std::abs( x ), std::abs( y ), std::abs( z ) };
	}

	vec3_t clamp( ) {
		for( size_t axis{ }; axis < 2; axis++ ) {
			auto &cur_axis = operator[]( axis );
			if( !std::isfinite( cur_axis ) ) {
				cur_axis = 0.f;
			}
		}

		x = std::clamp( x, -89.f, 89.f );
		y = std::clamp( std::remainder( y, 360.f ), -180.f, 180.f );
		z = 0.f;
		return *this;
	}

	vec3_t transform(  const matrix3x4_t& matrix ) const {
		auto out = vec3_t( );

		for (auto i = 0; i < 3; i++)
			out[i] = dot((vec3_t&)matrix[i]) + matrix[i][3];

		return out;
	}

public:
	float x, y, z;
};

__forceinline vec3_t operator*( float f, const vec3_t& v ) {
	return v * f;
}

class __declspec(align(16))VectorAligned : public vec3_t {
public:
	inline VectorAligned(void) { };

	inline VectorAligned(float x_, float y_, float z_) {
		x = x_; y = y_; z = z_;
	}

	explicit VectorAligned(const vec3_t& othr) {
		x = othr.x; y = othr.y; z = othr.z;
	}

	VectorAligned& operator=(const vec3_t& othr) {
		x = othr.x; y = othr.y; z = othr.z;
		return *this;
	}

	float w;
};

inline void matrix_copy( const matrix3x4_t& source, matrix3x4_t& target ) {
	for ( int i = 0; i < 3; i++ ) {
		for ( int j = 0; j < 4; j++ ) {
			target[ i ][ j ] = source[ i ][ j ];
		}
	}
}

inline void concat_transforms( const matrix3x4_t& in1, const matrix3x4_t& in2, matrix3x4_t& out ) {
	if ( &in1 == &out ) {
		matrix3x4_t in1b;
		matrix_copy( in1, in1b );
		concat_transforms( in1b, in2, out );
		return;
	}

	if ( &in2 == &out ) {
		matrix3x4_t in2b;
		matrix_copy( in2, in2b );
		concat_transforms( in1, in2b, out );
		return;
	}

	out[0][0] = in1[0][0] * in2[0][0] + in1[0][1] * in2[1][0] +
		in1[0][2] * in2[2][0];
	out[0][1] = in1[0][0] * in2[0][1] + in1[0][1] * in2[1][1] +
		in1[0][2] * in2[2][1];
	out[0][2] = in1[0][0] * in2[0][2] + in1[0][1] * in2[1][2] +
		in1[0][2] * in2[2][2];
	out[0][3] = in1[0][0] * in2[0][3] + in1[0][1] * in2[1][3] +
		in1[0][2] * in2[2][3] + in1[0][3];
	out[1][0] = in1[1][0] * in2[0][0] + in1[1][1] * in2[1][0] +
		in1[1][2] * in2[2][0];
	out[1][1] = in1[1][0] * in2[0][1] + in1[1][1] * in2[1][1] +
		in1[1][2] * in2[2][1];
	out[1][2] = in1[1][0] * in2[0][2] + in1[1][1] * in2[1][2] +
		in1[1][2] * in2[2][2];
	out[1][3] = in1[1][0] * in2[0][3] + in1[1][1] * in2[1][3] +
		in1[1][2] * in2[2][3] + in1[1][3];
	out[2][0] = in1[2][0] * in2[0][0] + in1[2][1] * in2[1][0] +
		in1[2][2] * in2[2][0];
	out[2][1] = in1[2][0] * in2[0][1] + in1[2][1] * in2[1][1] +
		in1[2][2] * in2[2][1];
	out[2][2] = in1[2][0] * in2[0][2] + in1[2][1] * in2[1][2] +
		in1[2][2] * in2[2][2];
	out[2][3] = in1[2][0] * in2[0][3] + in1[2][1] * in2[1][3] +
		in1[2][2] * in2[2][3] + in1[2][3];
}

inline void matrix_get_column( const matrix3x4_t& in, int column, vec3_t& out ) {
	out.x = in[0][column];
	out.y = in[1][column];
	out.z = in[2][column];
}

inline void matrix_set_column( const vec3_t& in, int column, matrix3x4_t& out ) {
	out[0][column] = in.x;
	out[1][column] = in.y;
	out[2][column] = in.z;
}

inline void angle_matrix(const vec3_t& angles, matrix3x4_t& matrix) {
	float sr, sp, sy, cr, cp, cy;

	SinCos(deg_to_rad(angles.y), &sy, &cy);
	SinCos(deg_to_rad(angles.x), &sp, &cp);
	SinCos(deg_to_rad(angles.z), &sr, &cr);

	matrix[0][0] = cp * cy;
	matrix[1][0] = cp * sy;
	matrix[2][0] = -sp;

	float crcy = cr * cy;
	float crsy = cr * sy;
	float srcy = sr * cy;
	float srsy = sr * sy;
	matrix[0][1] = sp * srcy - crsy;
	matrix[1][1] = sp * srsy + crcy;
	matrix[2][1] = sr * cp;

	matrix[0][2] = sp * crcy + srsy;
	matrix[1][2] = sp * crsy - srcy;
	matrix[2][2] = cr * cp;

	matrix[0][3] = 0.0f;
	matrix[1][3] = 0.0f;
	matrix[2][3] = 0.0f;
}

inline void angle_matrix( const vec3_t& angles, const vec3_t& position, matrix3x4_t& matrix ) {
	angle_matrix( angles, matrix );
	matrix_set_column( position, 3, matrix );
}

inline void get_matrix_origin( const matrix3x4_t& source, vec3_t& target ) {
	target.x = source[0][3];
	target.y = source[1][3];
	target.z = source[2][3];
}

inline void matrix_angles( const matrix3x4_t& matrix, vec3_t& angles ) {
	const vec3_t forward = { matrix[0][0], matrix[1][0], matrix[2][0] };
	const vec3_t left = { matrix[0][1], matrix[1][1], matrix[2][1] };
	const vec3_t up = { 0.f, 0.f, matrix[2][2] };

	float len = forward.length_2d( );

	if ( len > .001f ) {
		angles.x = rad_to_deg(std::atan2(-forward.z, len));
		angles.y = rad_to_deg(std::atan2(forward.y, forward.x));
		angles.z = rad_to_deg(std::atan2(left.z, up.z));
	}

	else {
		angles.x = rad_to_deg(std::atan2(-forward.z, len));
		angles.y = rad_to_deg(std::atan2(-left.x, left.y));
		angles.z = 0.f;
	}
}