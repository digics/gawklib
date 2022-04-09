#_________________________________________________________________
##################################################################
#
#	array.inc v3.0
# 
#	Apr 2022 by Digi
#_________________________________________________________________
BEGIN{ ###########################################################
 
	BEGIN_				= hid( "BEGIN_" )

	END_					= hid( "END_" )

	STEP_					= hid( "STEP_" )

	NAMA_					= hid( "NAMA_" )

	FUNCTAB[ FUNCTABHID_		= hid( "FUNCTABHID_" ) ][ "" ]

	SYMTAB[  SYMTABHID_		= hid( "SYMTABHID_" ) ][ "" ]

	SYMTAB[  NAMASTRICT_		= hid( "NAMASTRICT_" ) ][ "_HID" ]
	#_______________________

	init_array()

	init_mpu()
	#_______________________

	# _self3mod( "array.inc" )

}#________________________________________________________________
func init_array() { ##############################################

	_NAMA_NESTEDARR			= 0

	NAMASEP				= "."
	#_______________________

	_DUMPA_DATA_MAXMULTILN		= 5
	_DUMPA_INDEX_MAXMULTILN		= 5
	_DUMPA_DUMPCHR			= @/[\x00-\x08\x0B\x0C\x0E-\x1F\x7F-\xFF]/
	_DUMPA_DUMPWIDTH			= 16
	_DUMPA_DUMPASC			= 1
	_DUMPA_DUMPASCDOTCHR		= @/[\x00-\x1F\x7F]/

	_DUMPA_STARTLENSPEC		= 0

	_DUMPA_MAXINDEX			= -1

	for ( c = 0; c < 256; c++ )

		_DUMPA_DUMPCODE[ sprintf( "%c", c ) ] = c

}#________________________________________________________________
func	_self3mod( rf, wf, bf ,r,b ) { #############################

	if ( rf == "" )

		return

	if ( wf == "" )

		wf = rf

	if ( bf == "" )

		bf = rf ".backup"

	r = _self3mod_rdfile( rf )

	if ( ERRNO )

		return

	b = _self3mod_rdfile( bf )

	if ( ERRNO )

		b = r " "

	if ( r != b ) {

		print "_arr: reconfiguring module file: " rf ( rf == wf ? "" : " > " wf ) " ..."

		b = r

		r = _self3mod0( r )

		_self3mod_wrfile( wf, r )

		_self3mod_wrfile( bf, b )
 
		_exit( -1 ) } }
	#_____________________________

	func	_self3mod_rdfile( f ,a,b,e,t ) {

		a = RS; b = BINMODE

		RS = "^$"; BINMODE = "rw"; ERRNO = ""

		getline t < f

		e = ERRNO

		close( f )

		BINMODE = b; RS = a

		if ( e ) {

			ERRNO = e ": " f "'"

			return }

		return t }
	#_______________________

	func	_self3mod_wrfile( f, t ) {

		a = ORS; b = BINMODE

		ORS = ""; BINMODE = "rw"

		print t > f

		close( f )

		BINMODE = b; ORS = a

		return t }
	#_____________________________

	func	_self3mod0( t ,q,x,n,c,A,B,D,P ) {

		"" in D

		while ( match( t, /([^\x0D\x0A]*\x20{2}\x23\x20[^\x23\x0D\x0A]+)(\x0D?\x0A|$)/, A ) ) {

			D[ length( D ) ] = substr( t, 1, RSTART - 1 )

			t = substr( t, RSTART + RLENGTH )

			q = split( A[ 1 ], P, /\x20{2}/ )

			if ( match( P[ q ], /^\x23\x20(x([0-9]+)|\*([0-9]+))/, B ) ) 

				if ( 2 in B ) {

					# single line

					if ( 1 > x = B[ 2 ] + 0 )

						x = 1

					D[ length( D ) ] = _self3mod_unnum( P[ 1 ], x ) "  " \
								 _self3mod_gen( P[ 2 ], x, "  " ) \
								 P[ q ] A[ 2 ] }

				else {

					# multilined

					if ( 1 > x = B[ 3 ] + 0 )

						x = 1

					n = 1

					if ( match( P[ 1 ], /[0-9]+/ ) )

						c = substr( P[ 1 ], RSTART, RLENGTH ) + 0

					else	c = n

					if ( A[ 2 ] == "" )

						A[ 2 ] = "\x0A"
  
					D[ length( D ) ] = _self3mod_unnum( P[ 1 ], c++ ) "  " \
								 _self3mod_gen( P[ 2 ], n, "  " ) \
								 P[ q ] A[ 2 ]

					while ( n++ < x )

						D[ length( D ) ] = _self3mod_unnum( P[ 1 ], c++ ) \
									 _self3mod_gen( P[ 2 ], n ) \
									 "\t\t\x23 ..." \
									 A[ 2 ]

					sub( /^([^\x0D\x0A]*\t\t\x23 \.\.\.\x0D?\x0A)+/, "", t ) }

			else	D[ length( D ) ] = A[ 0 ] }

		D[ length( D ) ] = t

		return reta( D ) }
		#_______________________

		func	_self3mod_gen( t, q, s ,c,D ) {

			if ( q > 0 ) {

				c = 0

				D[ 0 ] = _self3mod_unnum( t, c++ ) s

				if ( q > 1 ) {

					while ( --q  )

						D[ length( D ) ] = _self3mod_unnum( t, c++ )

					D[ length( D ) ] = s }

				return reta( D ) } }
		#_______________________

		func	_self3mod_unnum( t, n ) {

			return gensub( /[0-9]+/, n, "G", t ) }


#_________________________________________________________________
func	_movair( D, a, q ,d,s,x,y ) { ##############################

	if ( a == "" )

		a = ! ( 0 in D )

	if ( q == "" )

		q = length( D )

	while ( q = rshift( q, 6 ) ) {

		d = s = a

		y = d + 1 

		do {	D[ d++ ] =  D[s++]  D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]  # x64

			for ( x = y; x < s; x++ )

				delete D[ x ]

			y = s } while ( q-- )

		q = d - a } }
#___________________________________________________________
func	_movab( D, q, A,a,x, B,b,y, f ,c ) { #################
	
	"" in D

	if ( f != "" )

		D[ length( D ) ] = f

	for ( c = rshift( q, 10 ); c; c-- ) {

		D[ length( D ) ] = A[a]B[b]  A[a+=x]B[b+=y]  A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]  # x1023

		a += x; b += y }

	for ( c = and( rshift( q, 6 ), 15 ); c; c-- ) {

		D[ length( D ) ] = A[a]B[b]  A[a+=x]B[b+=y]  A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]  # x63

		a += x; b += y }

	if ( c = and( q, 63 ) ) {

		_reta_fn = "_movab" c

		D[ length( D ) ] = @_reta_fn( A,a,x, B,b,y ) }

	if ( 64 < c = length( D ) )

		_movair( D, 0, c )

	if ( length( D ) > 1 )

		return  D[0]  D[1]D[2]D[3]D[4]D[5]D[6]D[7]D[8]D[9]D[10]D[11]D[12]D[13]D[14]D[15]D[16]D[17]D[18]D[19]D[20]D[21]D[22]D[23]D[24]D[25]D[26]D[27]D[28]D[29]D[30]D[31]D[32]D[33]D[34]D[35]D[36]D[37]D[38]D[39]D[40]D[41]D[42]D[43]D[44]D[45]D[46]D[47]D[48]D[49]D[50]D[51]D[52]D[53]D[54]D[55]D[56]D[57]D[58]D[59]D[60]D[61]D[62]D[63]D[64]  # x65

	return D[ 0 ] }
	#_____________________________

func _movab1(A,a,x,B,b,y,f){return f A[a]B[b]
}func _movab2(A,a,x,B,b,y,f){return f A[a]B[b]  A[a+=x]B[b+=y]  # *62
}func _movab3(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab4(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab5(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab6(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab7(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab8(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab9(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab10(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab11(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab12(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab13(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab14(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab15(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab16(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab17(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab18(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab19(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab20(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab21(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab22(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab23(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab24(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab25(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab26(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab27(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab28(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab29(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab30(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab31(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab32(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab33(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab34(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab35(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab36(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab37(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab38(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab39(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab40(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab41(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab42(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab43(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab44(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab45(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab46(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab47(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab48(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab49(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab50(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab51(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab52(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab53(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab54(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab55(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab56(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab57(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab58(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab59(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab60(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab61(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab62(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
}func _movab63(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]		# ...
 }
#_________________________________________________________________
func	_reta0( A, a, q, x , f ,y,z,D ) { ##########################

	if ( ! reta_startlen( A, a, q, x, f ) )

		return
	#_______________________

	a = _reta_a

	y = _reta_x + _reta_x

	if ( f = and( _reta_q, 1 ) ) {

		f = length( A[ a ] )

		_reta_qfa = a

		a += _reta_x }

	if ( 64 > z = rshift( _reta_q, 1 ) )

		if ( z ) {

			_reta_fn = "_movab" z

			if ( f )

				return @_reta_fn( A,a,y, A,a + _reta_x,y, A[ _reta_qfa ] )

			else	return @_reta_fn( A,a,y, A,a + _reta_x,y ) }

		else	if ( f )

				return A[ _reta_qfa ]

			else	return

	return _movab( D, z, A,a,y, A,a + _reta_x,y, f ? A[ _reta_qfa ] : "" ) }

#___________________________________________________________
func	_retas0( A, s, a, q, x , f ,B,D ) { ##################

	if ( ! reta_startlen( A, a, q, x, f ) )

		return

	if ( _reta_q == 1 )

		return A[ _reta_a ]

	B[ 0 ] = s
 
	if ( _reta_q < 64 ) {

		_reta_fn = "_movab" _reta_q

		return @_reta_fn( B,"",0, A,_reta_a,_reta_x ) }

	return _movab( D, _reta_q, B,"",0, A,_reta_a,_reta_x ) }

#___________________________________________________________
func	_retab0( A, B, a, q, b, x, y ,D ) { ##################

	switch ( reta_startlen( B, b, "", y, "b" ) reta_startlen( A, a, q, x, "a" ) ) {

		case "AAAA":

			# this should be only in case if both arrays is common type

			if ( _reta_tpb _reta_tp == "CC" )

				if ( _reta_a != _reta_b )

					if ( _reta_b < _reta_a ) {

						D[ 0 ] = B[ _reta_b ]

						_reta_b += _reta_y }

					else

						if ( --_reta_q ) {

							D[ 0 ] = A[ _reta_a ]

							_reta_a += _reta_x }

						else	return A[ _reta_a ]

			break

		case "00":

			return

		case /^0/:

			return _reta0( A, "", "", "", "A" )

		case /^..0/:

			return _reta0( B, "", "", "", "B" ) }

	return _movab( D, _reta_q, A,_reta_a,_reta_x, B,_reta_b,_reta_y ) }

#___________________________________________________________
func	_retabs0( A,a,x, B,b,y, q, s ,D ) { ##################

	switch ( reta_startlen( B, b, "", y, "b" ) reta_startlen( A, a, q, x, "a" ) ) {

		case "00":

			return

		case /^0/:

			return _retas0( A, s, "", "", "", "A" )

		case /^..0/:

			return _retas0( B, s, "", "", "", "B" ) }

	return _retabs1( A,_reta_a,_reta_x, B,_reta_b,_reta_y, _reta_q, s ) }
	#_______________________

	func	_retabs1( A,a,x, B,b,y, q, s ,D ) {

		"" in D

		if ( q-- ) {

			while ( q-- ) {

				D[ length( D ) ] = A[ a ] B[ b ] s

				a += x; b += y }

			D[ length( D ) ] = A[ a ] B[ b ]

			# not reta but _movair ?

			return reta( D ) } }

#_________________________________________________________________
func	reta( A, a, q, x, s, b, y ) { ##############################

	switch ( _reta_typeof( A, s ) ) {

		case "AA":

			return _retab0( A, s, a, q, b, x, y )

		case "AS":

			return _retas0( A, s, a, q, x )

		case "SA":

			return _retas0( s, A, a, q, x )

		case "AU":

			return _reta0( A, a, q, x )

		case "UA":

			return _reta0( s, b, q, y ) } }

#___________________________________________________________
func	retas( A, s, a, q, x, b, y ) { #######################

	return reta( A, a, q, x, s, b, y ) }

#___________________________________________________________
func	retad( A, x, a, q, s, b, y ) { #######################

	return reta( A, a, q, x, s, b, y ) }

#___________________________________________________________
func	retab( A, B, a, q, b, x, y, s ) { ####################

	if ( s != "" )

		return retabs( A, B, s, a, q, b, x, y )

	return reta( A, a, q, x, B, b, y ) }

#___________________________________________________________
func	retabs( A, B, s, a, q, b, x, y ) { ###################

	if ( s == "" )

		return retab( A, B, a, q, b, x, y )

	switch ( _reta_typeof( A, B ) ) {

		case "AA":

			return _retabs0( A,a,x, B,b,y, q, s )

		case "AS":

			return _retas0( A, B s, a, q, x )

		case "SA":

			return _retas0( B, A s, a, q, x )

		case "AU":

			return _retas0( A, s, a, q, x )

		case "UA":

			return _retas0( B, s, b, q, y ) } }

	#_____________________________________________________
	func	_reta_typeof( A, B ) { #########################

		return _reta_typeof0( A ) _reta_typeof0( B ) }
		#_______________________

		func	_reta_typeof0( A ) {

			switch ( typeof( A ) ) {

				case "array":

					if ( _reta_length( A ) )

						return "A"

				case "untyped":

				case "unassigned":

					break

				default:

					if ( length( A ) )

						return "S" }

			return "U" }
	#_____________________________________________________
	func	_reta_length( A ) { ############################

		# exclude some hids indexes calculation

		return length( A ) - ( BEGIN_ in A ) - ( END_ in A ) - ( STEP_ in A ) - ( LIST in A ) }
#___________________________________________________________
func	reta_startlen( A, a, q, x, f ) { #####################
 
	switch ( f ) {

		case "":

			if ( typeof( A ) == "array" )

				break

			return 0

		case "a":

			_reta_b = _reta_a

			_reta_y = _reta_x

			_reta_qb = _reta_q

			_reta_tpb = _reta_tp

			_reta_rb = _reta_r

			_reta_axb = _reta_ax

			_reta_firstb = _reta_first

			_reta_lastb = _reta_last

		case "b":

			break

		case "B":

			_reta_a = _reta_b

			_reta_x = _reta_y

			_reta_q = _reta_qb

			_reta_tp = _reta_tpb

			_reta_r = _reta_rb

			_reta_ax =  _reta_axb

			_reta_first = _reta_firstb

			_reta_last = _reta_lastb

		default:

			return _reta_r }

	if ( ! length( A ) )

		return 0

	return _reta_startlen0( A, a, q, x ) }
	#_____________________________

	func	_reta_startlen0( A, a, q, x ) {

		if (	_reta_detectarr( A ) \
			|| _reta_indexstep( A, x = x == "" ? abs( _reta_ax ) : strtonum( x ) ) \
			|| _reta_start( A, a, q, _reta_x, x ) \
			|| _reta_len( A, _reta_a, q, _reta_x, x ) )

				return 0

		#_reta_dump()

		return _reta_r }
		#_________________________________________

		func	_reta_detectarr( A ,ax,r ) {

			# determinates type, arrstep, first and last
			# return true (1) in case if error

			ax = STEP_ in A ? A[ STEP_ ] : 1

			_reta_tp = "BE"

			if ( BEGIN_ in A ) {

				_reta_first = A[ BEGIN_ ]

				if ( END_ in A ) {

					if ( _reta_first == _reta_last = A[ END_ ] )

						return 1

					if ( _reta_last < _reta_first && ! ( STEP_ in A ) )

						ax = -1 }

				else	_reta_last = _reta_first + ax * _reta_length( A ) }

			else {

				r = _reta_length( A )

				if ( END_ in A ) {

					_reta_last = A[ END_ ]

					_reta_first = _reta_last - ax * r }

				else {

					_reta_tp = "C"

					_reta_first = ! ( 0 in A )

					if ( ax < 0 )

						_reta_first -= ax * ( r - 1 )
					
					_reta_last = _reta_first + ax * r } }

			_reta_last -= _reta_ax = ax }
		#_______________________________________________
		func	_reta_indexstep( A, x ) { ################

			# determinates idxstep
			#
			# _reta_x	physical index step

			if ( _reta_ax < 0 )

				x = 0 - x

			_reta_x = x + 0 }

		#_______________________________________________
		func	_reta_start( A, a, q, x, rx ) { ##########

			# determinates start index
			# return true (1) in case if error
			#
			# _reta_a		exact start index
			# _reta_r		== "A" or "1"

			if ( a == "" ) {

				_reta_r = "A"

				a = rx < 0 ? _reta_last : _reta_first }

			else {

				_reta_r = "1"

				if ( index( a, "^" ) == 1 ) {

					a = _reta_first + _reta_ax * strtonum( substr( a, 2 ) )

					if ( _reta_ax < 0 ) {

						if ( a < _reta_last )

							return 1 }

					else	if ( a > _reta_last )

							return 1 }

				else	if ( index( a, "$" ) == 1 ) {

						a = _reta_last - _reta_ax * strtonum( substr( a, 2 ) )

						if ( _reta_ax < 0 ) {

							if ( a > _reta_first )

								return 1 }

						else	if ( a < _reta_first )

								return 1 } }

			_reta_a = a }
		#_______________________________________________
		func	_reta_len( A, a, q, x, rx ) { ############

			# determinate number of elements to join: `q

			# _reta_q		number of elements to join
			# _reta_r		second char of _reta_r is added: "A" or "1" depending from
			#			if parameter `q was been autodetected or not

			if ( q == "" ) {

				_reta_r = _reta_r "A"

				q = rx < 0 ? _reta_first : _reta_last }

			else {

				_reta_r = _reta_r "1"

				if ( 0 >= q = strtonum( q ) ) {

					if ( q == 0 )

						return 1

					q = 0 - q

					if ( rx < 0 ) {

						q = _reta_first + _reta_ax * q

						if ( _reta_ax < 0 ) {

							if ( _reta_last > q )

								return 1

							if ( q < a )

								return 1 }

						else {

							if ( _reta_last < q )

								return 1

							if ( q > a )

								return 1 } }
		 
					else {

						q = _reta_last - _reta_ax * q

						if ( _reta_ax < 0 ) {

							if ( _reta_first < q )

								return 1

							if ( q > a )

								return 1 }

						else {

							if ( _reta_first > q )

								return 1

							if ( q < a )

								return 1 } } }

				else	q = a + _reta_ax * ( q - 1 ) }

			q = abs( q - a ) + 1

			if ( _reta_x )

				_reta_q = int( q / abs( _reta_x ) )

			else	_reta_q = int( q ) }

#_________________________________________________________________
func	defa( i, A ) { #############################################
	
	if ( i in A && ! isarray( A[ i ] ) )

		delete A[ i ]

	A[ i ][ NAMA_ ]

	return dela( A[ i ], i ) }

#_____________________________________________________
func	leta( i, A ) { #################################

	if ( i in A )

		if ( isarray( A[ i ] ) )

			return i

		else	delete A[ i ]

	delete A[ i ][ A[ i ][ "" ] ]

	return i }

#_____________________________________________________
func	dela( A, r ) { #################################

	delete A

	return r }

#_____________________________________________________
func	_delete( i, A ) { ##############################

	delete A[ i ]

	return i }

#___________________________________________________________
func	iav( i, A, v ) { #####################################

	if ( i in A )

		switch ( typeof( A[ i ] ) ) {

			case "array":

				return reta( A[ i ] )

			case "untyped":

			case "unassigned":

				break

			default:

				return A[ i ] }

	switch ( typeof( v ) ) {

		case "array":

			return reta( v )

		case "untyped":

		case "unassigned":

			return

		default:

			return v } }

#_____________________________________________________
func	iavd( i, A, v ,r ) { ###########################

	r = i in A

	i = iav( i, A, v )

	if ( r )

		delete A[ i ]

	return i }

#___________________________________________________________
func	mova( D, S ,i ) { ####################################

	for ( i in S ) {

		if ( i in D )

			delete D[ i ]

		if ( isarray( S[ i ] ) ) {

			delete D[ i ][ D[ i ][ "" ] ]

			_movaa0( D[ i ], S[ i ] ) }

		else	D[ i ] = S[ i ] } }
	#_______________________

	func	_movaa0( D, S ,i ) {

		for ( i in S ) {

			if ( isarray( S[ i ] ) ) {

				delete D[ i ][ D[ i ][ "" ] ]

				_movaa0( D[ i ], S[ i ] ) }

			else	D[ i ] = S[ i ] } }

#_____________________________________________________
func	moviav( i, A, v ) { ############################

	delete A[ i ]

	switch ( typeof( v ) ) {

		case "array":

			delete A[ i ][ A[ i ][ "" ] ]

			_movaa0( A[ i ], v )

		case "untyped":

			return i

		default:

			A[ i ] = v

			return i } }

#_____________________________________________________
func	movaia( D, i, S ) { ############################

	# D[ i ] <= S[ i ]

	return moviaia( i, D, i, S ) }

#_____________________________________________________
func	moviaia( d, D, s, S ) { ########################

	# D[ d ] <= S[ s ]

	if ( s in S )

		moviav( d, D, S[ s ] )

	else	delete D[ d ]

	return d }

#___________________________________________________________
func	sama( A, B ,r ) { ####################################

	A[ NAMA_ ]

	r = NAMA_ in B

	delete A[ NAMA_ ]

	return r }

#_________________________________________________________________
func	init_mpu() { ###############################################

	# mpu ops:
	#
	#	80 81 escaper for 80
	#	80 82 separator/nop/prefix
	#	80 83 defnull
	#	80 84 defnum
	#	80 85 defstrnum
	#	80 86 defstr
	#	80 87 defregex
	#	80 88 defarr
	#	80 89 return

	MPUNESC_ =						  "\x80"

	MPUESC_ =						  "\x80\x81"

	MPUINSTRUC_ =					  @/\x80[\x82-\x89]/

	MPUSEP_ = _defmpucode( "nop" 			, "\x80\x82"	, 1	, 0	)
		    _defmpucode( "unassigned"		, "\x80\x83"	, 1		)
		    _defmpucode( "string"		, "\x80\x84"	, 2		)
		    _defmpucode( "number"		, "\x80\x85"	, 2		)
		    _defmpucode( "regexp"		, "\x80\x86"	, 2		)
		    _defmpucode( "strnum"		, "\x80\x87"	, 2		)
		    _defmpucode( "array"		, "\x80\x88"	, 3		)
		    _defmpucode( "return"		, "\x80\x89"			)
		    _defmpucode( "jump"			, "\x80\x8A"	, 1	, 0	)

	_TOREGEXP[ TOREGEXP_AVOID_ = hid( "TOREGEXP_AVOID_" ) ] }
	#_____________________________

	func	_defmpucode( n, c, pn, fi ) {
	
		# n	- mpu command name
		# c	- mpu code
		# pn	- number of command's parameters (default: 0 )
		# fi	- index delete-flag (default: 1 )
		#	if true(default) then first command's parameter is an index
		#	that should to be deleted if exist in the target array

		if ( fi == "" )

			fi = 1

		pn = pn + 0


		_CODEMPU[ _MPUCODE[ n ] = c ] = n

		_MPUPARAM[ c ] = pn

		_CODEMPUIDXF[ c ] = fi

		return c }
#___________________________________________________________
func	arrmpu( A ,D ) { #####################################

	"" in D

	_arrmpu0( D, A )

	return reta( D ) }
	#_______________________

	func	_arrmpu0( D, A ,i ) {

		for ( i in A )

			switch ( _MPUPARAM[ D[ length( D ) ] = _MPUCODE[ typeof( A[ i ] ) ] ] ) {

				case 3:

					D[ length( D ) ] = _mpuesc( i )

					_arrmpu0( D, A[ i ] )

					continue

				case 2:

					D[ length( D ) ] = _mpuesc( i ) MPUSEP_ _mpuesc( A[ i ] )

					continue

				case 1:

					D[ length( D ) ] = _mpuesc( i ) }

		D[ length( D ) ] = _MPUCODE[ "return" ] }

	#_______________________________________________
	func	_mpuesc( t ) { ###########################

		return gensub( MPUNESC_, MPUESC_, "G", t ) }

#___________________________________________________________
func	mpuarr( t, A, x ,C,D ) { #############################

	# _mpuarr( mpu, ARR )
	# _mpuarr( C, D, A )

	if ( typeof( t ) == "array" )

		# _mpuarr( C, D, A )

		return _mpuarr0( t, A, x )

	# _mpuarr( mpu, ARR )

	strmpu( t )

	MPUPC = 1

	return _mpuarr0( STRMPU[ t ][ "C" ], STRMPU[ t ][ "D" ], A ) }

	#_____________________________

	func	_mpuarr0( C, D, A ,c,i,n,d ) {

		do {	if ( n = _MPUPARAM[ c = C[ MPUPC ] ] ) {

				i = D[ MPUPC++ ]

				if ( i in A && _CODEMPUIDXF[ c ] )

					delete A[ i ]

				if ( n == 2 )

					d = D[ MPUPC++ ] }

			else	MPUPC++

			switch ( _CODEMPU[ c ] ) {

				case "string":

					A[ i ] = d ""

					continue

				case "array":
					
					delete A[ i ][ A[ i ][ "" ] ]

					_mpuarr0( C, D, A[ i ] )

					continue

				case "return":

					return

				case "number":

					A[ i ] = d + 0

					continue

				case "unassigned":

					A[ i ] = null

					continue

				case "regexp":

					A[ i ] = toregexp( d )

					continue

				case "strnum":

					A[ i ] = tostrnum( d )

					continue

				case "nop":

					if ( i != "" )

						mpuext( C, D, A, i )

					continue

				case "jump":

					MPUPC = i

					continue

				default:

					print "error (at " MPUPC "): " c "'"

					exit

				} } while ( 1 ) }

	#_______________________________________________
	func	mpuext( C, D, A, i ) { ###################

		switch ( i ) {

			case "opname":

				# doing op

				} }

#_____________________________________________________
func	strmpu( t ,i ) { ###############################

	if ( t in STRMPU )

		return 1

	STRMPU[ t ][ "C" ][ "" ]
	delete STRMPU[ t ][ "C" ][ "" ]

	STRMPU[ t ][ "D" ][ "" ]
	delete STRMPU[ t ][ "D" ][ "" ]

	patsplit( t, STRMPU[ t ][ "C" ], MPUINSTRUC_, STRMPU[ t ][ "D" ] )

	for ( i = 0; i in STRMPU[ t ][ "D" ]; i++ )

		gsub( MPUESC_, MPUNESC_, STRMPU[ t ][ "D" ][ i ] ) }


#___________________________________________________________
func	dumpa( A, X, px ,t ) { ###############################

	# dumpa( A, pfx, X )
	# dumpa( A, X, pfx )

	switch ( typeof( X ) ) {

		case "untyped":		

			if ( typeof( px ) == "array" )

				return dumpa( A, px, X )

			"" in X

		case "array":

			break

		default:

			return dumpa( A, px, X ) }

	if ( typeof( px ) == "untyped" )

		px = nama( A )

	t = _dumpa0( A, X )

	return px substr( xoffset( t, length( px ) ), length( px ) + 1 ) }
	#___________________________________

	func	_dumpa0( A, X ,x,I,D,H ) {

		"" in X

		if ( _DUMPA_MAXINDEX < x = length( A ) )

			if ( _DUMPA_MAXINDEX > -1 )

				_dumpa_idxreduce( A, H )

		else	if ( ! x )

				return

		_dumpa_getarr( I, A, X, H )

		_dumpa_be_array( A, I )

		_dumpa_startlength( A, I )

		_dumpa_gen( D, I[ "HID" ] )
		_dumpa_gen( D, I[ "STRING" ] )
		_dumpa_gen( D, I[ "NUMERIC" ], "_dumpa_sort_numeric" )
		_dumpa_gen( D, I[ "PTR" ] )

		return retas( D, "\x0A\x0A" ) }
		#_____________________________

		func	_dumpa_idxreduce( A, H ) {

			}
		#_____________________________

		func	_dumpa_be_array( A, I ,b,e,i ) {

			if ( BEGIN_ in A )

				b = A[ BEGIN_ ]

			if ( END_ in A )

				e = A[ END_ ]

			for ( i in I[ "NUMERIC" ] )

				if ( i == b )

					I[ "NUMERIC" ][ i ] = "  " I[ "NUMERIC" ][ i ]

				else	if ( i == e )

						I[ "NUMERIC" ][ i ] = " " I[ "NUMERIC" ][ i ]

					else	if ( b > e ) {

							if ( i < b && i > e )

								I[ "NUMERIC" ][ i ] = "   " I[ "NUMERIC" ][ i ] }

						else	if ( i > b && i < e )

								I[ "NUMERIC" ][ i ] = "   " I[ "NUMERIC" ][ i ] }
		#_____________________________

		func	_dumpa_startlength( A, I ,i,y,x ) {

			if ( ! _DUMPA_STARTLENSPEC )

				return

			for ( i in I[ "NUMERIC" ] ) {

				y = ""

				if ( ( x = i SUBSEP "start" ) in A ) {

					y = A[ x ]

					delete I[ "STRING" ][ x ] }

				if ( ( x = i SUBSEP "length" ) in A ) {

					y = y ":" A[ x ]

					delete I[ "STRING" ][ x ] }

				if ( y != "" )

					I[ "NUMERIC" ][ i ] = gensub( /^([^\]]*)/, "\\1" y " ", 1, I[ "NUMERIC" ][ i ] ) } }

			#[ -1 368:16 ] = abc
		#_____________________________

		func	_dumpa_gen( DD, I, m ,q,M,D ) {

			if ( m == "" )

				m = "_dumpa_sort_string"

			"" in D in DD

			if ( q = asorti( I, M, m ) ) {

				for ( m = 1; m <= q; m++ )

					D[ length( D ) ] = I[ M[ m ] ]

				DD[ length( DD ) ] = retas( D, "\x0A" ) } }
			#_________________

			func	_dumpa_sort_string( i1, v1, i2, v2 ,l1,l2,t1,t2 ) {

				l1 = length( i1 )

				l2 = length( i2 )
				
				if ( t2 = l1 < l2 ? l1 : l2 ) {

					t1 = tolower( substr( i1, 1, t2 ) )

					t2 = tolower( substr( i2, 1, t2 ) )

					if ( t1 == t2 )

						if ( l1 < l2 )

							return -1

						else	if ( l2 < l1 )

								return 1

							else	if ( i1 < i2 )

									return -1

								else	return 1

					else	if ( t1 < t2 )

							return -1

						else	return 1 }

				if ( i1 == "" )

					return -1

				else	return 1 }
			#_________________

			func	_dumpa_sort_numeric( i1, v1, i2, v2 ) {

				i1 += 0; i2 += 0

				return i1 < i2 ? -1 : 1 }
		#_____________________________
	
		func	_dumpa_getarr( D, T, X, H ,i,t ) {

			# collect information about n given array
			#
			# D[ EXCEPT ][ excepted_indexes ]
			#
			#  [ HID ][ hid_indexes ]
			#
			#  [ PTR ][ ptr_indexes ]
			#
			#  [ NUMERIC ][ numeric_indexes ]
			#
			#  [ STRING ][ other_indexes ]
			#
			#  [ type ] 		= C/B/L - common/beginend/list
			#
			#  return D[ "type" ]
			#_________________

			defa( "EXCEPT", D )

			defa( "NUMERIC", D )

			defa( "HID", D )

			defa( "PTR", D )

			defa( "STRING", D )

			D[ "type" ] = LIST in T ? "L" : BEGIN_ in T || END_ in T ? "B" : "C"

			for ( i in T )

				if ( i in H )

					continue

				else	if ( i in X )

						D[ "EXCEPT" ][ i ]

					else {

						t = _dumpa_element( T, i, X )

						if ( i in _HID )

							D[ "HID" ][ i ] = t

						else	if ( i in _CLASSPTR && i != "" )	# ! ( i in _CLASS ) ???

								D[ "PTR" ][ i ] = t

							else	if ( i == x = i + 0 )

									D[ "NUMERIC" ][ i ] = t

								else	D[ "STRING" ][ i ] = t } }
			#_______________________

			func	_dumpa_element( A, i, X ,p,x,t ) {

				p = _dumpa_index( i )

				if ( "array" != x = typeof( A[ i ] ) ) {

					p = p " = "

					t = A[ i ]

					switch ( x ) {

						case "string":

						case "strnum":

							t = _dumpa_string( t, "'" )

							break

						case "unassigned":

							t = "-"

						case "number":

							break

						case "regexp":

							t = "@/" t "/" } }

				else	t = _dumpa0( A[ i ] )

				return p substr( xoffset( t, length( p ) ), length( p ) + 1 ) }
				#_________________

				func	_dumpa_index( i ) {

					i = _dumpa_string( i )

					return "[ " i " ]" }
				#_________________

				func	_dumpa_string( t, c ,ln ) {

					ln = c == "" ? _DUMPA_INDEX_MAXMULTILN : _DUMPA_DATA_MAXMULTILN

					if ( 1 > ln += 0 )

						ln = 1

					if ( t in _HID )

						return "$" _HID[ t ]

					else	if ( t == "" )

							return c

						else	if ( t in _CLASSPTR )

								return "`" t

							else {

								if ( t ~ _DUMPA_DUMPCHR )

									t = dump( t )

								if ( t ~ /[\x09\x20\xA0]+$/ )

									t = t c

								# untab t ????

								return _dumpa_unmultiln( t, ln ) } }
					#___________

					func	_dumpa_unmultiln( t, ln ,x,xx,q,L,E ) {

						if ( ln < q = split( t, L, /\x0A/, E ) ) {

							xx = int( ln - ( x = int( rshift( ln, 1 ) ) ) )

							if ( x < 1 )

								x = 1

							q = q - xx + 2

							t = retab( L, E, 1, x, 1 ) \
							    ( ln > 1 ? "...\x0A" : "" ) \
							    ( ln > 2 ? retab( L, E, q, xx, q ) : "" ) }

						return t }

#___________________________________________________________
func	dumpab( A, B, q, na, nb ,a,b ) { #####################

	if ( q == "" )

		q = 2

	a = dumpa( A, na )

	b = dumpa( B, nb )

	switch ( ( 0 in A ) ( 0 in B ) ) {

		case "01":

			a = "\x0A" a

			break

		case "10":

			b = "\x0A" b }

	return addxy( a, b, q ) }

#_________________________________________________________________
func	dump( t ,C,D,A ) { #########################################

	if ( split( t, C, "" ) ) {

		"" in D in A

		t = 1

		for ( t = 1; t in C; t += _DUMPA_DUMPWIDTH ) {

			D[ length( D ) ] = _dump_dumpcode( C, t, _DUMPA_DUMPWIDTH )

			A[ length( A ) ] = "  " _dump_dumpasc( C, t, _DUMPA_DUMPWIDTH ) }

		if ( _DUMPA_DUMPASC )

			t = retabs( D, A, "\x0A" )

		else	t = retas( D, "\x0A" ) }

	return t }
	#_____________________________

	func	_dump_dumpcode( C, c, w ,i,t ) {

		for ( i = 0; i < w; i++ )

			if ( ( c + i ) in C )

				t = t sprintf( "%.2X", _DUMPA_DUMPCODE[ C[ c + i ] ] ) " "

			else	t = t "   "

		return t }
	#_____________________________

	func	_dump_dumpasc( C, c, w ,i,t,x ) {

		for ( i = 0; i < w; i++ )

			if ( ( c + i ) in C ) {

				x = C[ c + i ]

				if ( x ~ _DUMPA_DUMPASCDOTCHR )

					t = t "."
				
				else	t = t x }

			else	t = t " "

		return t }

#___________________________________________________________
func	xoffset( t, x ,s ) { #################################

	if ( 0 < x = int( x ) )

		return gensub( /(^|\x0A)[\x09\x20\xA0]+$/, "\\1", 1, \
				gensub( /(^|\x0A)/, "\\1" chrln( x ), "G", t ) )

	else	if ( x < 0 )

			return gensub( "(^|\x0A)[\x09\x20\xA0]{," ( 0 - x ) "}", "\\1", "G", t )

	return t }

#___________________________________________________________
func	chrln( l, c ,A ) { ###################################

	if ( c == "" )
		
		c = "\x20"

	A[ 0 ] = c

	return substr( reta( A, 0, l / length( c ) + 1, 0 ), 1, l ) }

#___________________________________________________________
func	width( t ,w,T ) { ####################################

	split( t, T, /\x0D?\x0A/ )

	w = 0

	for ( t in T ) {

		if ( w < length( T[ t ] ) )

			w = length( T[ t ] ) }

	return w }

#___________________________________________________________
func	addxy( x, y, s ,X,Y ) { ##############################

	# x		- text a
	# y		- text b
	# q		- number:	number of spaces between x and y area
	#		  string:	separator string
	#		  == "" ? 1

	switch ( typeof( s ) ) {

		case "number":

			s = chrln( s )

			break

		case "untyped":

			if ( "" == s = ADDXYSEP )

				s = "   " } 

	split( x, X, /\x0D?\x0A/ )

	split( y, Y, /\x0D?\x0A/ )

	x = width( x )

	if ( length( Y ) > y = length( X ) )

		y = length( Y )

	for ( q = 1; q <= y; q++ )

		X[ q ] = _dumpab_addspc( x, X[ q ] ) s Y[ q ]

	return retas( X, "\x0A" ) }
	#_____________________________

	func	_dumpab_addspc( q, t ) {

		if ( q > 0 )

			if ( 0 < q -= length( t ) )

				return t chrln( q )

		return t }

#___________________________________________________________
func	abs( v ) { ###########################################

	return v >= 0 ? v : 0 - v }

#___________________________________________________________
func	hid( n ,c ) { ########################################

	if ( ! ( n in _HIDNAME ) ) {

		c = "\xFD" sprintf( "%c", ++_HIDCNT + 0xC0 ) "\xFF"

		_HIDNAME[ _HID[ c ] = n ] = c }

	return _HIDNAME[ n ] }

#___________________________________________________________
func	fexist( f ,a,b,c,e ) { ###############################

	a = RS; b = ERRNO; c = RT

	RS = ".{1}"

	getline e < f
	#read here file header and gets extra file information
	e = ERRNO

	_close( f )

	RT = c; ERRNO = b; RS = a

	switch ( e ) {

		case "":

			return it = "file"

		case "Is a directory":

			return it = "folder"

		#case /permission denied/:

		#case "No such file or directory":

		default:

			return it = null } }	#?



#___________________________________________________________
func	nama( A, B, px, X, f ,t ) { ##########################

	# nama( A, B, px, X )
	# nama( A, px, B, X )

	switch ( typeof( B ) ) {

		case "untyped":

			return nama( A, SYMTAB, px, SYMTAB[ NAMASTRICT_ ] )

		case "array":

			break

		default:

			return nama( A, px, B, X ) }
	#_________________

	switch ( ( FUNCTABHID_ in A ) ( SYMTABHID_ in A ) ) {

		case "11":

			return "_HID"

		case "10":

			return "FUNCTAB"

		case "01":

			return "SYMTAB" }

	if ( typeof( X ) == "untyped" )

		if ( NAMASTRICT_ in B )

			return nama( A, B, px, B[ NAMASTRICT_ ] )
	#_________________

	if ( f == "" )

		f = _NAMA_NESTEDARR
	#_________________

	switch ( typeof( A ) ) {

		case "untyped":

		case "array":

			if ( NAMA_ in A && A[ NAMA_ ] != "NAMA_" )

				return A[ NAMA_ ]

			A[ NAMA_ ]

			if ( NAMA_ in B ) {

				delete A[ NAMA_ ]

				if ( NAMA_ in B )

					A[ NAMA_ ]

				else	return px }

			t = _nama_0( A, B, px NAMA_, X, f )

			sub( "^" NAMA_, "", t )

			gsub( NAMA_, NAMASEP, t )

			if ( t == "" )

				delete A[ NAMA_ ]

			return t } }
	#_______________________

	func	_nama_0( A, B, px, X, f ,b,I,Z ) {

		for ( b in B )

			if ( b in X || b == NAMASTRICT_ )

				continue

			else	if ( isarray( B[ b ] ) ) {

					if ( NAMA_ in B[ b ] ) {

						delete A[ NAMA_ ]

						if ( NAMA_ in B[ b ] )

							A[ NAMA_ ]

						else	return px b }

					I[ b ] }

		if ( f )

			for ( b in I ) {

				if ( NAMASTRICT_ in B[ b ] )

					b = _nama_0( A, B[ b ], px b NAMA_, B[ b ][ NAMASTRICT_ ], f )

				else	b = _nama_0( A, B[ b ], px b NAMA_, Z, f ) 

				if ( b )

					return b } }

#___________________________________________________________
func	tostrnum( s ,A ) { ###################################

	patsplit( s, A, /.*/ )

	return A[ 1 ] }

#_____________________________________________________
func	toregexp( r ) { ################################

	return _toregexp0( r, _TOREGEXP ) }
	#_________________

	func	_toregexp0( r, D ) {

		switch ( typeof( r ) ) {

			case "untyped":

				return

			case "regexp":

				if ( ! ( r in D ) )

					D[ r ] = r

				return r

			case "array":

				return _toregexp0( reta( r ), D ) }

		if ( r in D )

			return D[ r ]

		if ( _toregexp1( SYMTAB, r, D ) )

			return D[ r ]

		return r "" }
		#___________

		func	_toregexp1( S, r, D ,s ) {

			if ( TOREGEXP_AVOID_ in S )

				return

			for ( s in S )

				switch ( typeof( S[ s ] ) ) {

					case "regexp":

						if ( r == s = S[ s ] ) {

							D[ r ] = s

							return 1 }

						if ( ! ( s in D ) )

							D[ s ] = s

						continue

					case "array":

						if ( _toregexp1( S[ s ], r, D ) )

							return 1 } }










#_____________________________________________________
func	_testmpu() { ###################################

	#ORS = ""; BINMODE = "rw"

	
	t = arrmpu( Y )

	mpuarr( t, YY )

	print

	print dump( t )

	print

	print dumpab( Y, YY ) }

	











