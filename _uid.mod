


#_________________________________________________________________
## UID v2.8 ( 2021.3.11 ) ########################################


#_________________________________________________________________
func	_getuid( p ,csp,h,l,cp ) { #################################

	if ( p in _UIDCPTR ) {

		csp = _UIDCSPTR[ p ]
		
		h = _UIDCNTH[ cp = _UIDCPTR[ p ] ]

		if ( "" != l = _UIDCSL[ csp ][ _UIDCNTL[ cp ] ] ) {

			_UIDCNTL[ cp ] = l
			
			return _UIDPFX[ p ] h l _UIDSFX[ p ] }

		if ( "" != _UIDCNTH[ cp ] = h = _UIDCSH[ csp ][ h ] )

			return _UIDPFX[ p ] h ( _UIDCNTL[ cp ] = _UIDCSL[ csp ][ "" ] ) _UIDSFX[ p ]

		return _errOutOfUID( p ) }

	return _errUndefinedUIDGEN( p ) }
#___________________________________________________________
func	_uidset( p, px, sx, a,b,c,d ) { ######################

	_UIDCSPTR[ p ] = _UIDCPTR[ p ] = p

	_UIDPFX[ p ] = px
	
	_UIDSFX[ p ] = sx

	_UIDCNTH[ p ] = ""
	
	_uidset_0( p, _UIDCSH, a,b )
		
	_UIDCNTL[ p ] = _uidset_0( p, _UIDCSL, c,d )
	
	return p }
	#_____________________________

	func	_uidset_0( p, D, a, b ,pv,A,B ) {

		_uidset_a( A, a )

		_uidset_a( B, b )

		_defa( p, D )

		if ( length( A ) )

			for ( a = ! ( 0 in A ); a in A; a++ )

				pv = _uidset_1( D[ p ], B, A[ a ], pv )
		
		else	pv = _uidset_1( D[ p ], B )

		return pv }
		#_________________
		
		func	_uidset_1( D, B, px, pv ,b,n ) {

			if ( length( B ) )

				for ( b = ! ( 0 in B ); b in B; b++ )

					if ( ! ( ( n = px B[ b ] ) in D ) )
	
						pv = D[ pv ] = n
						
			else	if ( ! ( px in D ) )
			
					pv = D[ pv ] = px
					
			return D[ "\x7F" ] = pv }
		#_______________________

		func	_uidset_a( D, c, q,i,A,B ) {

			split( c, A, "" )

			delete D

			if ( q = asort( A, A, "@val_str_asc" ) )

				do { if ( ! ( ( c = A[ ++i ] ) in B ) )
				
					B[ D[ length( D ) ] = c ] } while ( i < q ) }
#_____________________________________________________
func	_uidcnt( p, px, sx, pp ) { #####################

	if ( pp in _UIDCSPTR ) {

		_UIDPFX[ p ] = px; _UIDSFX[ p ] = sx

		_UIDCPTR[ p ] = _UIDCPTR[ pp ]
		
		_UIDCSPTR[ p ] = _UIDCSPTR[ pp ]
		
		return p }

	return _fatal( "_uidchr: undefined character set source uidgen: @1'", pp ) }
#_____________________________________________________
func	_uidchr( p, px, sx, pp ) { #####################

	if ( pp in _UIDCSPTR ) {

		_UIDCPTR[ p ] = p

		_UIDCSPTR[ p ] = _UIDCSPTR[ pp ]

		_UIDPFX[ p ] = px

		_UIDSFX[ p ] = sx

		_UIDCNTH[ p ] = ""

		_UIDCNTL[ p ] = _UIDCSL[ pp ][ "\x7F" ]
		
		return p }

	return _fatal( "_uidchr: undefined character set source uidgen: @1'", pp ) }
#___________________________________________________________
func	_isuidgen( p ) { #####################################

	if ( p in _UIDCPTR )
		
		return it = "G" }
#_____________________________________________________
func	_errOutOfUID( p ) { ############################

	return _fatal( px "uidgen @1: out of uids", p ) }
#_______________________________________________
func	_errUndefinedUIDGEN( p ) { ###############

	return _fatal( px "undefined uid generator: @1", p ) }	
#_________________________________________________________________
##################################################################


