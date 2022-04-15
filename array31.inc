


#_________________________________________________________________
##################################################################
#
#     array.inc v3.1
# 
#     Apr 2022 by Digi
#_________________________________________________________________
BEGIN{ ###########################################################

      DELETE_                       = hid( "DELETE_" )

      STACK_                        = hid( "STACK_" )
      LIST_                         = hid( "LIST_" )
 
      BEGIN_                        = hid( "BEGIN_" )
      END_                          = hid( "END_" )
      STEP_                         = hid( "STEP_" )




      FUNCTAB[ FUNCTABHID_          = hid( "FUNCTABHID_" ) ][ "" ]
      SYMTAB[  SYMTABHID_           = hid( "SYMTABHID_" ) ][ "" ]
      SYMTAB[  NAMASTRICT_          = hid( "NAMASTRICT_" ) ][ "_HID" ]

      NAMA_                         = hid( "NAMA_" )




      _TOREGEXP[ TOREGEXP_AVOID_    = hid( "TOREGEXP_AVOID_" ) ]



      NOREGEXP_                     = hid( "NOREGEXP_" )


      #_______________________

      init_env()

      init_string()

      init_array()

      init_mpu()
      #_______________________

      #_self3mod( "//localhost/env/awk/mod/arr/2022_RELEASE/array.inc" )
}#________________________________________________________________
func  init_env() { ###############################################

      for ( f in FUNCTAB )

            _FUNCTAB[ f ] = f

}#__________________________________________________________
func  hid( n ,c ) { ########################################

      if ( ! ( n in _HIDNAME ) ) {

            c = "\xFD" sprintf( "%c", ++_HIDCNT + 0xC0 ) "\xFF"

            _HIDNAME[ _HID[ c ] = n ] = c }

      return _HIDNAME[ n ] }

#___________________________________________________________
func  def( n, a,b,c,d,e,f ) { ##############################

      if ( isfunc( "def_" n ) )

            return @fn( a,b,c,d,e,f )

      else  _fatal( "def: no function: @1", is ) }

#___________________________________________________________
func  pushenv( A ,i ) { ####################################

      defa( i = length( A[ leta( STACK_, A ) ] ), A[ STACK_ ] )

      return enva( A, A[ STACK_ ][ i ] ) }

#_____________________________________________________
func  popenv( A ,i,B ) { #############################

      if ( STACK_ in A \
           && \
           i = length( A[ STACK_ ] ) ) {

            "" in B

            enva( A[ STACK_ ][ --i ], B )

            if ( i )

                  delete A[ STACK_ ][ i ]

            else  delete A[ STACK_ ] } }

#_____________________________________________________
func  swapenv( A ) { #################################

      return enva( A ) }

#_____________________________________________________
func  enva( A, D ,i,a,B ) { ##########################

      "" in A

      if ( typeof( D ) == "array" )

            for ( i in A )

                  if ( i in _HID )

                        continue

                  else {

                        if ( i in SYMTAB ) {

                              a = SYMTAB[ i ]

                              SYMTAB[ i ] = A[ i ] }

                        else {

                              if ( i in PROCINFO )

                                    a = PROCINFO[ i ]

                              else  a = DELETE_

                              if ( A[ i ] == DELETE_ )

                                    delete PROCINFO[ i ]

                              else  PROCINFO[ i ] = A[ i ] }

                        D[ i ] = a }

      else  return enva( A, A ) }
#___________________________________________________________
func  isfunc( f ) { ########################################

      is = null

      switch ( typeof( f ) ) {

            case "untyped":

                  it = "U"

                  return

            case "unassigned":

                  it = "u"

                  return

            case "array":

                  it = "A"

                  return

            default:

                  is = p

                  if ( f in _FUNCTAB ) {

                        fn = _FUNCTAB[ f ]

                        return it = "F" }

                  it = "S" } }

#_________________________________________________________________ COMMON
func  errno( a,b,c,d ) { #########################################

      return ERRNO }

#_____________________________________________________
func  nerrno( a,b,c,d ) { ############################

      return ! ERRNO }

#_________________________________________________________________ STRING
func  init_string() { ############################################

      DUMP_WIDTH                    = 16
      DUMP_FLAG                     = "ADC"
      DUMP_DOTCHR                   = @/[\x00-\x1F\x7F]/
      #_______________________

      for ( c = 0; c < 256; c++ )

            CHR[ sprintf( "%c", c ) ] = c }

#_________________________________________________________________ ARRAY
func init_array() { ##############################################

      NAMA_NESTEDARR                = 0
      NAMASEP                       = "."
      #_______________________

      DUMPA_DEFAULT_MAXLEV          = 3

      DUMPA_MAXHEIGHT               = 5

      DUMPA_DUMPCHR                 = @/[\x00-\x08\x0B\x0C\x0E-\x1F\x7F-\xFF]|^[\x0D\x0A\x20\xA0\x09]*$/

      DUMPA_MAXINDEX                = -1

      DUMPA_BEFX                    = 1
      DUMPA_STARTLENFX              = 0

}#__________________________________________________________ JOIN
func  _movair( D, a, q ,d,s,x,y ) { ########################

      if ( a == "" )

            a = ! ( 0 in D )

      if ( q == "" )

            q = length( D )

      while ( q = rshift( q, 6 ) ) {

            d = s = a

            y = d + 1 

            do {  D[ d++ ] =  D[s++]  D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]D[s++]  # x64

                  for ( x = y; x < s; x++ )

                        delete D[ x ]

                  y = s } while ( q-- )

            q = d - a } }
#_____________________________________________________
func  _movab( D, q, A,a,x, B,b,y, f ,c ) { ###########
      
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
      }func _movab3(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]          # ...
      }func _movab4(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]        # ...
      }func _movab5(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]            # ...
      }func _movab6(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]          # ...
      }func _movab7(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]        # ...
      }func _movab8(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]            # ...
      }func _movab9(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]          # ...
      }func _movab10(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]       # ...
      }func _movab11(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]           # ...
      }func _movab12(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]         # ...
      }func _movab13(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]       # ...
      }func _movab14(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]           # ...
      }func _movab15(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]         # ...
      }func _movab16(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]       # ...
      }func _movab17(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]           # ...
      }func _movab18(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]         # ...
      }func _movab19(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]       # ...
      }func _movab20(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]           # ...
      }func _movab21(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]         # ...
      }func _movab22(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]       # ...
      }func _movab23(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]           # ...
      }func _movab24(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]         # ...
      }func _movab25(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]       # ...
      }func _movab26(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]           # ...
      }func _movab27(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]         # ...
      }func _movab28(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]       # ...
      }func _movab29(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]           # ...
      }func _movab30(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]         # ...
      }func _movab31(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]       # ...
      }func _movab32(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]           # ...
      }func _movab33(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]         # ...
      }func _movab34(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]       # ...
      }func _movab35(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]           # ...
      }func _movab36(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]         # ...
      }func _movab37(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]       # ...
      }func _movab38(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]           # ...
      }func _movab39(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]         # ...
      }func _movab40(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]       # ...
      }func _movab41(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]           # ...
      }func _movab42(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]         # ...
      }func _movab43(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]       # ...
      }func _movab44(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]           # ...
      }func _movab45(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]         # ...
      }func _movab46(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]       # ...
      }func _movab47(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]           # ...
      }func _movab48(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]         # ...
      }func _movab49(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]       # ...
      }func _movab50(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]           # ...
      }func _movab51(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]         # ...
      }func _movab52(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]       # ...
      }func _movab53(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]           # ...
      }func _movab54(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]         # ...
      }func _movab55(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]       # ...
      }func _movab56(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]           # ...
      }func _movab57(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]         # ...
      }func _movab58(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]       # ...
      }func _movab59(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]           # ...
      }func _movab60(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]         # ...
      }func _movab61(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]       # ...
      }func _movab62(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]           # ...
      }func _movab63(A,a,x,B,b,y,f){return f A[a]B[b]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]A[a+=x]B[b+=y]         # ...
      }

#___________________________________________________________
func  reta_startlen( A, a, q, x, f ) { #####################
 
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
      #___________________________________

      func  _reta_startlen0( A, a, q, x ) {

            if (  _reta_detectarr( A ) \
                  || _reta_indexstep( A, x = x == "" ? abs( _reta_ax ) : strtonum( x ) ) \
                  || _reta_start( A, a, q, _reta_x, x ) \
                  || _reta_len( A, _reta_a, q, _reta_x, x ) )

                        return 0

            return _reta_r }
            #_____________________________

            func  _reta_detectarr( A ,ax,r ) {

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

                        else  _reta_last = _reta_first + ax * reta_length( A ) }

                  else {

                        r = reta_length( A )

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
            #_____________________________

            func  _reta_indexstep( A, x ) {

                  # determinates idxstep
                  #
                  # _reta_x   physical index step

                  if ( _reta_ax < 0 )

                        x = 0 - x

                  _reta_x = x + 0 }
            #_____________________________

            func  _reta_start( A, a, q, x, rx ) {

                  # determinates start index
                  # return true (1) in case if error
                  #
                  # _reta_a         exact start index
                  # _reta_r         == "A" or "1"

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

                              else  if ( a > _reta_last )

                                          return 1 }

                        else  if ( index( a, "$" ) == 1 ) {

                                    a = _reta_last - _reta_ax * strtonum( substr( a, 2 ) )

                                    if ( _reta_ax < 0 ) {

                                          if ( a > _reta_first )

                                                return 1 }

                                    else  if ( a < _reta_first )

                                                return 1 } }

                  _reta_a = a }
            #_____________________________

            func  _reta_len( A, a, q, x, rx ) {

                  # determinate number of elements to join: `q

                  # _reta_q         number of elements to join
                  # _reta_r         second char of _reta_r is added: "A" or "1" depending from
                  #                 if parameter `q was been autodetected or not

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

                        else  q = a + _reta_ax * ( q - 1 ) }

                  q = abs( q - a ) + 1

                  if ( _reta_x )

                        _reta_q = int( q / abs( _reta_x ) )

                  else  _reta_q = int( q ) }

#___________________________________________________________
func  _reta_typeof( A, B ) { ###############################

      return _reta_typeof0( A ) _reta_typeof0( B ) }
      #_________________

      func  _reta_typeof0( A ) {

            switch ( typeof( A ) ) {

                  case "array":

                        if ( reta_length( A ) )

                              return "A"

                  case "untyped":

                  case "unassigned":

                        break

                  default:

                        if ( length( A ) )

                              return "S" }

            return "U" }

#_____________________________________________________
func  reta_length( A ) { #############################

      # exclude some hids indexes calculation

      return length( A ) - ( BEGIN_ in A ) - ( END_ in A ) - ( STEP_ in A ) - ( LIST in A ) }

#___________________________________________________________
func  reta( A, a, q, x, s, b, y ) { ########################

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

      #___________________________________

      func  _reta0( A, a, q, x , f ,y,z,D ) {

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

                        else  return @_reta_fn( A,a,y, A,a + _reta_x,y ) }

                  else  if ( f )

                              return A[ _reta_qfa ]

                        else  return

            return _movab( D, z, A,a,y, A,a + _reta_x,y, f ? A[ _reta_qfa ] : "" ) }

#_____________________________________________________
func  retas( A, s, x, a, q, b, y ) { #################

      return reta( A, a, q, x, s, b, y ) }

      #___________________________________

      func  _retas0( A, s, a, q, x , f ,B,D ) {

            if ( ! reta_startlen( A, a, q, x, f ) )

                  return

            if ( _reta_q == 1 )

                  return A[ _reta_a ]

            B[ 0 ] = s
       
            if ( _reta_q < 64 ) {

                  _reta_fn = "_movab" _reta_q

                  return @_reta_fn( B,"",0, A,_reta_a,_reta_x ) }

            return _movab( D, _reta_q, B,"",0, A,_reta_a,_reta_x ) }

#_____________________________________________________
func  retad( A, x, q, a, s, b, y ) { #################

      return reta( A, a, q, x, s, b, y ) }

#_____________________________________________________
func  retab( A, B, a, q, b, x, y, s ) { ##############

      if ( s != "" )

            return retabs( A, B, s, a, q, b, x, y )

      return reta( A, a, q, x, B, b, y ) }

      #___________________________________

      func  _retab0( A, B, a, q, b, x, y ,D ) {

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

                                          else  return A[ _reta_a ]

                        break

                  case "00":

                        return

                  case /^0/:

                        return _reta0( A, "", "", "", "A" )

                  case /^..0/:

                        return _reta0( B, "", "", "", "B" ) }

            return _movab( D, _reta_q, A,_reta_a,_reta_x, B,_reta_b,_reta_y ) }

#_____________________________________________________
func  retabs( A, B, s, a, q, b, x, y ) { #############

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

      #___________________________________

      func  _retabs0( A,a,x, B,b,y, q, s ,D ) {

            switch ( reta_startlen( B, b, "", y, "b" ) reta_startlen( A, a, q, x, "a" ) ) {

                  case "00":

                        return

                  case /^0/:

                        return _retas0( A, s, "", "", "", "A" )

                  case /^..0/:

                        return _retas0( B, s, "", "", "", "B" ) }

            return _retabs1( A,_reta_a,_reta_x, B,_reta_b,_reta_y, _reta_q, s ) }
            #_______________________

            func  _retabs1( A,a,x, B,b,y, q, s ,D ) {

                  "" in D

                  if ( q-- ) {

                        while ( q-- ) {

                              D[ length( D ) ] = A[ a ] B[ b ] s

                              a += x; b += y }

                        D[ length( D ) ] = A[ a ] B[ b ]

                        # not reta but _movair ?

                        return reta( D ) } }

#________________________________________________________________
func  init_mpu() { ############################################## MPU

      MPUNESC_ =                                        "\x80"

      MPUESC_ =                                         "\x80\x81"

      MPUSEP_ = def( "mpucode",     "nop"             , "\x80\x82"      , 1   , 0   )
                def( "mpucode",     "unassigned"      , "\x80\x83"      , 1         )
                def( "mpucode",     "string"          , "\x80\x84"      , 2         )
                def( "mpucode",     "number"          , "\x80\x85"      , 2         )
                def( "mpucode",     "regexp"          , "\x80\x86"      , 2         )
                def( "mpucode",     "strnum"          , "\x80\x87"      , 2         )
                def( "mpucode",     "array"           , "\x80\x88"      , 3         )
                def( "mpucode",     "return"          , "\x80\x89"                  )
                def( "mpucode",     "jump"            , "\x80\x8A"      , 1   , 0   )

      MPUINSTRUC_ =                        @/\x80[\x82-\x8A]/

}#__________________________________________________________
func  def_mpucode( n, c, pn, fi, d,e,f ) { #################

      # n   - mpu command name
      # c   - mpu code
      # pn  - number of command's parameters (default: 0 )
      # fi  - index delete-flag (default: 1 )
      #     if true(default) then first command's parameter is an index
      #     that should to be deleted if exist in the target array

      if ( fi == "" )

            fi = 1

      pn = pn + 0

      _CODEMPU[ _MPUCODE[ n ] = c ] = n

      _MPUPARAM[ c ] = pn

      _CODEMPUIDXF[ c ] = fi

      return c }

#_____________________________________________________
func  expa( A ,D ) { #################################

      "" in D

      _expa0( D, A )

      return reta( D ) }
      #_______________________

      func  _expa0( D, A ,i ) {

            for ( i in A )

                  switch ( _MPUPARAM[ D[ length( D ) ] = _MPUCODE[ typeof( A[ i ] ) ] ] ) {

                        case 3:

                              D[ length( D ) ] = mpuesc( i )

                              _expa0( D, A[ i ] )

                              continue

                        case 2:

                              D[ length( D ) ] = mpuesc( i ) MPUSEP_ mpuesc( A[ i ] )

                              continue

                        case 1:

                              D[ length( D ) ] = mpuesc( i ) }

            D[ length( D ) ] = _MPUCODE[ "return" ] }

#_____________________________________________________
func  impa( t, A, pc ,C,D ) { ########################

      # impa( mpu, ARR )
      #
      # mpu - mpu string
      # A   - target array
      # x   - 

      if ( typeof( t ) == "array" )

            # impa( C, D, A )
            #
            # C   - code array
            # D   - data array
            # A   - target array

            return _mpuarr0( t, A, pc )

      # impa( t, ARR, pc )
      #
      # t   - mpu string
      # A   - target array
      # pc  - mpu instruction ptr

      if ( pc == "" )

            pc = 1

      mpustr( t )

      MPUPC = pc

      return _impa0( MPUSTR[ t ][ "C" ], MPUSTR[ t ][ "D" ], A ) }

      #_____________________________

      func  _impa0( C, D, A ,c,i,n,d ) {

            do {  if ( n = _MPUPARAM[ c = C[ MPUPC ] ] ) {

                        i = D[ MPUPC++ ]

                        if ( i in A && _CODEMPUIDXF[ c ] )

                              delete A[ i ]

                        if ( n == 2 )

                              d = D[ MPUPC++ ] }

                  else  MPUPC++

                  switch ( _CODEMPU[ c ] ) {

                        case "string":

                              A[ i ] = d ""

                              continue

                        case "array":
                              
                              delete A[ i ][ A[ i ][ "" ] ]

                              _impa0( C, D, A[ i ] )

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

                                    mpuop( C, D, A, i )

                              continue

                        case "jump":

                              MPUPC = i

                              continue

                        default:

                              print "error (at " MPUPC "): " c "'"

                              exit

                        } } while ( 1 ) }

#_____________________________________________________
func  mpustr( t ,i ) { ###############################

      if ( t in MPUSTR )

            return 1

      MPUSTR[ t ][ "C" ][ "" ]
      delete MPUSTR[ t ][ "C" ][ "" ]

      MPUSTR[ t ][ "D" ][ "" ]
      delete MPUSTR[ t ][ "D" ][ "" ]

      patsplit( t, MPUSTR[ t ][ "C" ], MPUINSTRUC_, MPUSTR[ t ][ "D" ] )

      for ( i = 0; i in MPUSTR[ t ][ "D" ]; i++ )

            gsub( MPUESC_, MPUNESC_, MPUSTR[ t ][ "D" ][ i ] ) }

#_____________________________________________________
func  mpuesc( t ) { ##################################

      return gensub( MPUNESC_, MPUESC_, "G", t ) }

#_____________________________________________________
func  mpunesc( t ) { #################################

      return gensub( MPUESC_, MPUNESC_, "G", t ) }

#_____________________________________________________
func  mpuop( C, D, A, i ) { ##########################

      switch ( i ) {

            case "opname":

                  # doing op

                  } }
#_________________________________________________________________ ARRAY DEFINITION
func  defa( i, A ) { #############################################
      
      if ( i in A && ! isarray( A[ i ] ) )

            delete A[ i ]

      A[ i ][ NAMA_ ]

      return dela( A[ i ], i ) }

#_____________________________________________________
func  leta( i, A ) { #################################

      if ( i in A )

            if ( isarray( A[ i ] ) )

                  return i

            else  delete A[ i ]

      delete A[ i ][ A[ i ][ "" ] ]

      return i }

#___________________________________________________________
func  dela( A, r ) { #######################################

      delete A

      return r }

#___________________________________________________________
func  _delete( i, A ) { ####################################

      delete A[ i ]

      return i }

#_________________________________________________________________ DATA TRANSFER
func  iav( i, A, v ) { ###########################################

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
func  iavd( i, A, v ,r ) { ###########################

      r = i in A

      i = iav( i, A, v )

      if ( r )

            delete A[ i ]

      return i }

#___________________________________________________________
func  mova( D, S ,i ) { ####################################

      for ( i in S ) {

            if ( i in D )

                  delete D[ i ]

            if ( isarray( S[ i ] ) ) {

                  delete D[ i ][ D[ i ][ "" ] ]

                  _movaa0( D[ i ], S[ i ] ) }

            else  D[ i ] = S[ i ] } }
      #_______________________

      func  _movaa0( D, S ,i ) {

            for ( i in S ) {

                  if ( isarray( S[ i ] ) ) {

                        delete D[ i ][ D[ i ][ "" ] ]

                        _movaa0( D[ i ], S[ i ] ) }

                  else  D[ i ] = S[ i ] } }

#_____________________________________________________
func  moviav( i, A, v ) { ############################

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
func  movaia( D, i, S ) { ############################

      # D[ i ] <= S[ i ]

      return moviaia( i, D, i, S ) }

#_____________________________________________________
func  moviaia( d, D, s, S ) { ########################

      # D[ d ] <= S[ s ]

      if ( s in S )

            moviav( d, D, S[ s ] )

      else  delete D[ d ]

      return d }

#_________________________________________________________________ DUMP
func  dumpa( A, a,b,c,d,e,f,g,h, X, pc ,t,U ) { ##################

      # dumpa( A, pfx, X )
      # dumpa( A, X, pfx )

      if ( pc < 8 ) {

            if ( ! pc++ ) {

                  _dumpa_title = null

                  _dumpa_maxlev = DUMPA_DEFAULT_MAXLEV

                  _wrmac( "dumpa.stricted", DELETE_ )

                  _wrmac( "dumpa.granted", DELETE_ ) }

            switch ( typeof( a ) ) {

                  case "untyped":         

                  case "unassigned":

                        #print "param " pc ": -"

                        break

                  case "array":

                        #print "param " pc ": is array X"

                        return dumpa( A, b,c,d,e,f,g,h,U, a, pc )

                  case "number":

                        #print "param " pc ": maxlevel = " a "'"

                        # dumpa( A, 1 )

                        _dumpa_maxlev = a

                        break

                  case "string":

                  case "strnum":

                        if ( index( a, "~!" ) == 1 ) {

                              a = substr( a, 3 )

                              #print "param " pc ": stricted = " a "'"

                              _wrmac( "dumpa.stricted", a )

                              break }

                        else  if ( index( a, "~" ) == 1 )

                                    a = substr( a, 2 )

                              else {

                                    #print "param " pc ": title = " a "'"

                                    _dumpa_title = a

                                    break }

                  case "regexp":

                        #print "param " pc ": granted = " a "'"

                        # dumpa( A, @/index/ )

                        _wrmac( "dumpa.granted", a ) }

            return dumpa( A, b,c,d,e,f,g,h,U, X, pc ) }

      if ( typeof( _dumpa_title ) == "unassigned" )

            _dumpa_title = nama( A )

      _dumpa_lev = 0

      if ( NOREGEXP_ != _dumpa_stricted = _rdmac( "dumpa.stricted" ) )

            _dumpa_strictedf = 1 

      if ( NOREGEXP_ != _dumpa_granted = _rdmac( "dumpa.granted" ) )

            _dumpa_grantedf = 1 

      t = _dumpa0( A, X )

      return _dumpa_title substr( xoffset( t, length( _dumpa_title ) ), length( _dumpa_title ) + 1 ) }

      #___________________________________

      func  _dumpa0( A, X ,x,I,D,H ) {

            "" in X

            if ( DUMPA_MAXINDEX < x = length( A ) )

                  if ( DUMPA_MAXINDEX > -1 )

                        _dumpa_idxreduce( A, H )

            else  if ( ! x )

                        return

            _dumpa_getarr( I, A, X, H )

            _dumpa_be_array( A, I )

            _dumpa_startlength( A, I )

            _dumpa_gen( D, I[ "HID" ] )
            _dumpa_gen( D, I[ "STRING" ] )
            _dumpa_gen( D, I[ "NUMERIC" ], "_dumpa_sort_numeric" )
            _dumpa_gen( D, I[ "PTR" ] )

            x = reta( D )

            x = lasteoloff( x )

            gsub( /\x0A\x0A\x0A/, "\x0A\x0A", x )

            return x }
            #_____________________________

            func  _dumpa_idxreduce( A, H ) {

                  }
            #_____________________________

            func  _dumpa_be_array( A, I ,b,e,i ) {

                  if ( ! DUMPA_BEFX )

                        return

                  if ( BEGIN_ in A )

                        b = A[ BEGIN_ ]

                  if ( END_ in A )

                        e = A[ END_ ]

                  for ( i in I[ "NUMERIC" ] )

                        if ( i == b )

                              I[ "NUMERIC" ][ i ] = "  " I[ "NUMERIC" ][ i ]

                        else  if ( i == e )

                                    I[ "NUMERIC" ][ i ] = " " I[ "NUMERIC" ][ i ]

                              else  if ( b > e ) {

                                          if ( i < b && i > e )

                                                I[ "NUMERIC" ][ i ] = "   " I[ "NUMERIC" ][ i ] }

                                    else  if ( i > b && i < e )

                                                I[ "NUMERIC" ][ i ] = "   " I[ "NUMERIC" ][ i ] }
            #_____________________________

            func  _dumpa_startlength( A, I ,i,y,x ) {

                  if ( ! DUMPA_STARTLENFX )

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

            func  _dumpa_gen( DD, I, m ,q,M,D ) {

                  if ( m == "" )

                        m = "_dumpa_sort_string"

                  "" in D in DD

                  if ( q = asorti( I, M, m ) ) {

                        for ( m = 1; m <= q; m++ )

                              D[ length( D ) ] = I[ M[ m ] ]

                        m = lasteoloff( retas( D, "\x0A" ) )

                        #print; print "m: " m "'"; print

                        if ( m !~ /^[\x09\x0A\x0D\x20\xA0]*$/ )

                              DD[ length( DD ) ] = m "\x0A\x0A" } }
                  #_________________

                  func  _dumpa_sort_string( i1, v1, i2, v2 ,l1,l2,t1,t2 ) {

                        l1 = length( i1 )

                        l2 = length( i2 )
                        
                        if ( t2 = l1 < l2 ? l1 : l2 ) {

                              t1 = tolower( substr( i1, 1, t2 ) )

                              t2 = tolower( substr( i2, 1, t2 ) )

                              if ( t1 == t2 )

                                    if ( l1 < l2 )

                                          return -1

                                    else  if ( l2 < l1 )

                                                return 1

                                          else  if ( i1 < i2 )

                                                      return -1

                                                else  return 1

                              else  if ( t1 < t2 )

                                          return -1

                                    else  return 1 }

                        if ( i1 == "" )

                              return -1

                        else  return 1 }
                  #_________________

                  func  _dumpa_sort_numeric( i1, v1, i2, v2 ) {

                        i1 += 0; i2 += 0

                        return i1 < i2 ? -1 : 1 }
            #_____________________________
      
            func  _dumpa_getarr( D, T, X, H ,i,t ) {

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
                  #  [ type ]             = C/B/L - common/beginend/list
                  #
                  #  return D[ "type" ]
                  #_________________

                  defa( "STRICT", D )

                  defa( "UNGRANT", D )

                  defa( "EXCEPT", D )

                  defa( "NUMERIC", D )

                  defa( "HID", D )

                  defa( "PTR", D )

                  defa( "STRING", D )

                  D[ "type" ] = LIST in T ? "L" : BEGIN_ in T || END_ in T ? "B" : "C"

                  for ( i in T )

                        if ( i in H )

                              continue

                        else  if ( i in X && i != "" ) {

                                    D[ "EXCEPT" ][ i ]

                                    continue }

                              else  if ( _dumpa_strictedf && i ~ _dumpa_stricted ) {

                                          D[ "STRICT" ][ i ]

                                          continue }

                                    else  if ( _dumpa_grantedf && i !~ _dumpa_granted ) {

                                                D[ "UNGRANT" ][ i ]

                                                continue }

                                          else {

                                                t = _dumpa_element( T, i, X )

                                                if ( i in _HID )

                                                      D[ "HID" ][ i ] = t

                                                else  if ( i in _CLASSPTR && i != "" )    # ! ( i in _CLASS ) ???

                                                            D[ "PTR" ][ i ] = t

                                                      else  if ( i == x = i + 0 )

                                                                  D[ "NUMERIC" ][ i ] = t

                                                            else  D[ "STRING" ][ i ] = t } }
                  #_______________________

                  func  _dumpa_element( A, i, X ,p,x,t,ti,B ) {

                        ti = _dumpa_index( i )

                        if ( "array" != x = typeof( A[ i ] ) ) {

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

                                          t = "@/" t "/" }

                              t = addxy( " = ", t ) }

                        else {

                              if ( _dumpa_maxlev == -1 || _dumpa_maxlev >= ++_dumpa_lev )

                                    t = _dumpa0( A[ i ], B )

                              else  if ( length( A[ i ] ) )

                                          t = "[ ..."

                              --_dumpa_lev }

                        t = addxy( ti, t )

                        if ( t ~ /\x0A/ )

                              t = t "\x0A"

                        return t }
                        #_________________

                        func  _dumpa_index( i ) {

                              i = _dumpa_string( i )

                              return addxy( addxy( "[ ", i ), " ]" ) } 
                        #_________________

                        func  _dumpa_string( t, c ,ln ) {

                              ln = c == "" ? DUMPA_MAXHEIGHT : DUMPA_MAXHEIGHT

                              if ( 1 > ln += 0 )

                                    ln = 1

                              if ( t in _HID )

                                    return "$" _HID[ t ]

                              else  if ( t == "" )

                                          return c

                                    else  if ( t in _CLASSPTR )

                                                return "`" t

                                          else {

                                                if ( t ~ DUMPA_DUMPCHR )

                                                      t = lasteoloff( dump( t, "8DC" ) )

                                                else  if ( t ~ /[\x09\x20\xA0]+$/ )

                                                      t = t c

                                                # untab t ????

                                                return _dumpa_unmultiln( t, ln ) } }
                              #___________

                              func  _dumpa_unmultiln( t, ln ,x,xx,q,L,E ) {

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
func  dumpab( A, B, q, na, nb ,a,b ) { #####################

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

#___________________________________________________________
func  dump( t, w, s, e ,af,df,cf,aw,C,D ) { ################

      # t   - source data
      # w   - width/flags:
      #
      #           A     - address output is enabled
      #           D     - data output is enabled
      #           C     - character output is enabled
      #
      #           default: "" ( DUMP_FLAG )
      #
      # s   - dump start address
      # e   - dump end address

      if ( split( t, C, "" ) ) {

            if ( "" == cf = gensub( /[0-9]+/, "", "G", w ) )

                  cf = DUMP_FLAG

            af = gsub( /A/, "", cf )

            df = gsub( /D/, "", cf )

            cf = gsub( /C/, "", cf )

            if ( 1 > w = int( w ) )

                  w = DUMP_WIDTH

            if ( s == "" || 0 > s = int( s ) )

                  s = 0

            if ( e == "" || 0 > e = int( e ) )

                  e = length( C ) - 1

            aw = "%." length( sprintf( "%.2X", length( C ) - 1 ) ) "X"

            "" in D

            s++; e++

            while ( s <= e ) {

                  t = ""

                  if ( df )

                        t = _dump_code( C, s, w, e )

                  else  t = ""

                  if ( cf )

                        t = ( t == "" ? "" : t " " ) _dump_asc( C, s, w, e )

                  t = ( af ? sprintf( aw, s - 1 ) ( t == "" ? "" : ": " ) : "" ) t

                  if ( t != "" )

                        t = t "\x0A"

                  D[ length( D ) ] = t

                  s += w }

            return reta( D ) } }
      #_____________________________

      func  _dump_code( C, s, w, e ,t ) {

            if ( e >= s + w )

                  e = s + w - 1

            do {  if ( s <= e )

                        t = t sprintf( "%.2X", CHR[ C[ s++ ] ] ) " "

                  else  t = t "   " } while ( --w )

            return t }
      #_____________________________

      func  _dump_asc( C, s, w, e ,t ) {

            if ( e >= s + w )

                  e = s + w - 1

            do {  if ( s <= e ) {

                        x = C[ s++ ]

                        if ( x ~ DUMP_DOTCHR )

                              t = t "."
                        
                        else  t = t x }

                  else  t = t " " } while ( --w )

            return t }



#_________________________________________________________________ OTHER ARRAY
func  sama( A, B ,r ) { ##########################################

      A[ NAMA_ ]

      r = NAMA_ in B

      delete A[ NAMA_ ]

      return r }

#_____________________________________________________
func  nama( A, B, px, X, f ,t ) { ####################

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

            f = NAMA_NESTEDARR
      #_________________

      switch ( typeof( A ) ) {

            case "array":

                  if ( NAMA_ in A && A[ NAMA_ ] != "NAMA_" )

                        return A[ NAMA_ ]

            case "untyped":

                  A[ NAMA_ ]

                  if ( NAMA_ in B ) {

                        delete A[ NAMA_ ]

                        if ( NAMA_ in B )

                              A[ NAMA_ ]

                        else  return px }

                  t = _nama_0( A, B, px NAMA_, X, f )

                  sub( "^" NAMA_, "", t )

                  gsub( NAMA_, NAMASEP, t )

                  if ( t == "" )

                        delete A[ NAMA_ ]

                  return t } }
      #_______________________

      func  _nama_0( A, B, px, X, f ,b,I,Z ) {

            for ( b in B )

                  if ( b in X || b == NAMASTRICT_ )

                        continue

                  else  if ( isarray( B[ b ] ) ) {

                              if ( NAMA_ in B[ b ] ) {

                                    delete A[ NAMA_ ]

                                    if ( NAMA_ in B[ b ] )

                                          A[ NAMA_ ]

                                    else  return px b }

                              I[ b ] }

            if ( f )

                  for ( b in I ) {

                        if ( NAMASTRICT_ in B[ b ] )

                              b = _nama_0( A, B[ b ], px b NAMA_, B[ b ][ NAMASTRICT_ ], f )

                        else  b = _nama_0( A, B[ b ], px b NAMA_, Z, f ) 

                        if ( b )

                              return b } }



#___________________________________________________________ NUMBER
func  abs( v ) { ###########################################

      return v >= 0 ? v : 0 - v }

#___________________________________________________________ STRING
func  addxy( x, y, s ,dx,dy,mx,X,Y ) { #####################

      # x         - text a
      # y         - text b
      # s         - number:   number of spaces between x and y area
      #             string:   separator string
      #             == "" ? 1

      if ( typeof( s ) == "number" )

            s = chrln( s )

      x = tobox( x ); dx = tobox_width

      y = tobox( y ); dy = tobox_width

      x = split( x, X, /\x0D?\x0A/ )

      y = split( y, Y, /\x0D?\x0A/ )

      if ( x < mx = y )

            while ( x < y )

                  X[ y-- ] = chrln( dx )

      else  if ( y < mx = x )

            while ( x > y )

                  Y[ x-- ] = chrln( dy )

      for ( q = 1; q <= mx; q++ )

            X[ q ] = X[ q ] s Y[ q ]

      return retas( X, "\x0A" ) }

#_____________________________________________________
func  tobox( t, w ,l,T,E ) { #########################

      if ( w == "" )

            w = width( t )

      else  w += 0

      tobox_width = w

      if ( split( t, T, /\x0D?\x0A/, E ) ) {

            for ( t in T )

                  if ( w < l = length( T[ t ] ) )

                        T[ t ] = substr( T[ t ], 1, w - 3 ) "..."

                  else  if ( w > l )

                              T[ t ] = T[ t ] chrln( w - l )

            t = retab( T, E ) }

      return t }
#_____________________________________________________
func  xoffset( t, x ,s ) { ###########################

      if ( 0 < x = int( x ) )

            return gensub( /(^|\x0A)/, "\\1" chrln( x ), "G", t )

      else  if ( 0 < x = 0 - x )

                  return gensub( "(^|\x0A)[\x09\x20\xA0]{," x "}", "\\1", "G", t )

      return t }

#_____________________________________________________
func  width( t ,w,T ) { ##############################

      split( t, T, /\x0D?\x0A/ )

      w = 0

      for ( t in T )

            if ( w < length( T[ t ] ) )

                  w = length( T[ t ] )

      return w }

#_____________________________________________________
func  lasteoloff( t ) { ##############################

      return gensub( /(\x0D?\x0A[\09\x20\xA0]*)+$/, "", 1, t ) }

#_____________________________________________________
func  chrln( l, c ,A ) { #############################

      if ( c == "" )
            
            c = "\x20"

      A[ 0 ] = c

      return substr( dup( l / length( c ) + 1, c ), 1, l ) }

#_____________________________________________________
func  dup( n, t ,A ) { ###############################

      if ( 1 <= n = int( n ) ) {

            A[ 0 ] = t

            return reta( A, 0, n, 0 ) } }

#_____________________________________________________
func  rev( t ,T ) { ##################################

      split( t, T, "" )

      return retad( T, -1 ) }
#_____________________________________________________
func  tostrnum( s ,A ) { #############################

      switch ( typeof( s ) ) {

            case "untyped":

                  return

            case "array":

                  return tostrnum( reta( s ) )

            case "strnum":

                  return s }

      patsplit( s, A, /.*/ )

      return A[ 1 ] }

#_____________________________________________________
func  toregexp( r ) { ################################

      return _toregexp0( r, _TOREGEXP ) }
      #_________________

      func  _toregexp0( r, D ) {

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

            func  _toregexp1( S, r, D ,s ) {

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

#___________________________________________________________ IO
func  isexist( f ,e ) { ####################################

      pushenv( ISEXIST )

      getline e < f

      #read here file header and gets extra file information
      
      e = ERRNO

      _close( f )

      popenv( ISEXIST )

      is = f

      switch ( e ) {

            case "":

                  return it = "file"

            case "Is a directory":

                  return it = "folder"

            #case /permission denied/:

            #case "No such file or directory":

            default:

                  return it = null } }    #?
      #_____________________________

      BEGIN{ ISEXIST[ "RT" ] = ""
             ISEXIST[ "ERRNO" ] = ""
             ISEXIST[ "RS" ] = ".{1}" }

#_____________________________________________________
func  rdfile( f ,e,t ) { #############################

      #RDFILE[ f, "TIMEOUT" ] = ???

      #RDFILE[ f, "RETRY" ] = ???

      pushenv( RDFILE )

      getline t < f

      e = ERRNO

      close( f )

      popenv( RDFILE )

      delete RDFILE[ f, "TIMEOUT" ]

      delete RDFILE[ f, "RETRY" ]

      if ( e ) {

            ERRNO = e ": " f "'"

            return }

      return t }
      #_____________________________

      BEGIN{ RDFILE[ "RS" ] = "^$"
             RDFILE[ "ERRNO" ] = ""
             RDFILE[ "BINMODE" ] = "rw" }

#_____________________________________________________
func  wrfile( f, t ) { ###############################

      WRFILE[ f, "NONFATAL" ] = 1

      pushenv( WRFILE )

      print t > f

      close( f )

      popenv( WRFILE )

      delete WRFILE[ f, "NONFATAL" ]

      return t }  
      #_____________________________

      BEGIN{ WRFILE[ "ORS" ] = ""
             WRFILE[ "ERRNO" ] = ""
             WRFILE[ "BINMODE" ] = "rw" }

#________________________________________________________________
func  _self3mod( rf, wf, bf ,r,b ) { ############################

      if ( rf == "" )

            return

      if ( wf == "" )

            wf = rf

      if ( bf == "" )

            bf = rf ".backup"

      r = rdfile( rf )

      if ( ERRNO )

            return

      b = rdfile( bf )

      if ( ERRNO )

            b = r " "

      if ( r != b ) {

            print "_arr: reconfiguring module file: " rf ( rf == wf ? "" : " > " wf ) " ..."

            b = r

            r = _self3mod0( r )

            wrfile( wf, r )

            wrfile( bf, b )
 
            exit -1 } }
      #_____________________________

      func  _self3mod0( t ,q,x,n,c,A,B,D,P ) {

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

                              else  c = n

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

                  else  D[ length( D ) ] = A[ 0 ] }

            D[ length( D ) ] = t

            return reta( D ) }
            #_______________________

            func  _self3mod_gen( t, q, s ,c,D ) {

                  if ( q > 0 ) {

                        c = 0

                        D[ 0 ] = _self3mod_unnum( t, c++ ) s

                        if ( q > 1 ) {

                              while ( --q  )

                                    D[ length( D ) ] = _self3mod_unnum( t, c++ )

                              D[ length( D ) ] = s }

                        return reta( D ) } }
            #_______________________

            func  _self3mod_unnum( t, n ) {

                  return gensub( /[0-9]+/, n, "G", t ) }

#_________________________________________________________________
##################################################################













# switch myenv to using array.inc




func  adda( A, d ) {

      x = STEP_ in A ? A[ STEP_ ] : 1

      if ( END_ in A ) {

            if ( BEGIN_ in A && ! ( STEP_ in A ) && A[ BEGIN_ ] > A[ END_ ] )

                  x = -1

            moviav( A[ END_ ], A, d )

            A[ END_ ] += x }

      else  if ( BEGIN_ in A )

                  moviav( A[ BEGIN_ ] + x * reta_length( A ), A, d )

            else  moviav( ! ( 0 in A ) + x * length( A ), A, d ) }


func  insa( A, d ) {

      x = STEP_ in A ? A[ STEP_ ] : 1

      if ( BEGIN_ in A ) {

            moviav( A[ END_ ], A, d )

            A[ END_ ] += x }

      else  if ( BEGIN_ in A )

                  moviav( A[ BEGIN_ ] + x * reta_length( A ), A, d )

            else  moviav( ! ( 0 in A ) + x * length( A ), A, d ) }





func  _wrmac( n, t ) {

      if ( t == DELETE_ )

            delete MAC[ n ]

      else  if ( t != NOREGEXP_ && t != "" )

                  MAC[ n ][ length( MAC[ leta( n, MAC ) ] ) ] = t

      return n }

func  _rdmac( n ,U ) {

      if ( n in MAC )

            return "(" retas( MAC[ n ], ")|(", -1 ) ")"

      else  return NOREGEXP_ }




#_____________________________________________________
func  _testmpu() { ###################################



      t = expa( Y )

      impa( t, YY )
 
      print length( t ) "'"

      print "-----------------------"

      print dump( t )

      print "+++++++++++++++++++++++"

      print dumpab( Y, YY )

 }





