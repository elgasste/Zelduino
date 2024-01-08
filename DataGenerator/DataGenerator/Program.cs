using System.IO;
using System.Windows.Media;
using System.Windows;
using System.Windows.Media.Imaging;

// TODO: put these in another file, and also make them 2d arrays
int[] _worldMapTextureIndexes0 =
{
   2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
   2,2,2,2,2,2,2,2,2,2,2,3,0,0,2,2,
   2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,
   2,0,0,0,0,0,0,0,0,8,0,0,0,0,4,2,
   2,0,0,0,0,0,0,0,0,0,0,8,0,0,0,4,
   2,0,0,8,0,0,8,0,0,8,0,0,0,0,0,0,
   2,0,0,0,0,0,0,0,0,0,0,8,0,0,0,7,
   2,0,0,0,0,0,0,0,0,8,0,0,0,0,7,2,
   2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,
   2,6,6,6,6,6,6,6,6,6,6,6,6,6,2,2,
   2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2
};

int[] _collisionMapPassable0 =
{
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,
   0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,
   0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,
   0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,
   0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,
   0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,0,0,
   0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,0,0,
   0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,
   0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,
   0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,
   0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,
   0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,0,0,0,
   0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,
   0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,
   0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

int[] _worldMapTextureIndexes1 =
{
   2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
   2,2,2,2,1,2,3,0,0,2,2,2,2,2,2,2,
   2,2,2,3,0,0,0,0,0,2,2,2,2,2,2,2,
   2,2,3,0,0,0,0,0,0,2,2,2,2,2,2,2,
   2,3,0,0,0,0,0,0,0,2,2,2,2,2,2,2,
   0,0,0,0,0,0,0,0,0,4,2,2,2,2,2,2,
   2,5,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
   2,2,0,0,0,0,0,0,0,0,0,0,0,0,6,6,
   2,2,0,0,0,0,0,0,0,0,0,0,0,0,2,2,
   2,2,6,6,6,6,6,6,6,6,6,6,6,6,2,2,
   2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2
};

int[] _collisionMapPassable1 =
{
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
   0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
   0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,
   0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,
   0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,
   0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

var _palette = new List<ushort>();
var _textTextureMap = new List<byte>();
var _worldTextureMap = new List<byte>();
var _playerTextureMap = new List<byte>();

Console.WriteLine();
Console.WriteLine( "=====================================================" );
Console.WriteLine( "               ZELDUINO DATA GENERATOR" );
Console.WriteLine( "=====================================================" );
Console.WriteLine();

void BitmapSanityCheck( BitmapSource bitmap )
{
   if ( bitmap.Format != PixelFormats.Indexed8 )
   {
      throw new Exception( "Expecting image pixel format to be Indexed8" );
   }
   else if ( bitmap.PixelWidth <= 0 || bitmap.PixelWidth % 16 != 0 )
   {
      throw new Exception( "Image width should be a multiple of 16" );
   }
   else if ( bitmap.PixelHeight <= 0 || bitmap.PixelWidth % 16 != 0 )
   {
      throw new Exception( "Image height should be a multiple of 16" );
   }
}

static ushort ColortoUInt16( Color color )
{
   var r16 = (ushort)( ( color.R / 255.0 ) * 31 );
   var g16 = (ushort)( ( color.G / 255.0 ) * 63 );
   var b16 = (ushort)( ( color.B / 255.0 ) * 31 );

   return (ushort)( ( r16 << 11 ) | ( g16 << 5 ) | b16 );
}

static Color GetPixelColor( BitmapSource bitmap, int x, int y )
{
   var bytesPerPixel = (int)Math.Truncate( ( bitmap.Format.BitsPerPixel + 7.0 ) / 8.0 );
   int stride = bitmap.PixelWidth * bytesPerPixel;
   byte[] pixel = new byte[1];
   var rect = new Int32Rect( x, y, 1, 1 );

   bitmap.CopyPixels( rect, pixel, stride, 0 );
   return bitmap.Palette.Colors[pixel[0]];
}

static ushort GetPixelColor16( BitmapSource bitmap, int x, int y ) => ColortoUInt16( GetPixelColor( bitmap, x, y ) );

int PaletteIndexFromColor( ushort color )
{
   if ( _palette is null )
   {
      throw new Exception( "Somehow the palette is null, no idea how it happened." );
   }
   else if ( _palette.Count > 15 )
   {
      throw new Exception( "Trying to add too many colors to the palette." );
   }

   int paletteIndex = _palette.IndexOf( color );

   if ( paletteIndex < 0 )
   {
      _palette.Add( color );
      paletteIndex = _palette.Count - 1;
   }

   return paletteIndex;
}

void LoadTextTextureMap( BitmapSource bitmap )
{
   if ( _textTextureMap is null )
   {
      throw new Exception( "Somehow the text texture map is null, no idea how it happened." );
   }

   for ( int row = 0; row < bitmap.PixelHeight; row++ )
   {
      for ( int col = 0; col < bitmap.PixelWidth; col += 8 )
      {
         _textTextureMap.Add( 0x00 );

         for ( int i = 0; i < 8; i++ )
         {
            var pixelColor = GetPixelColor( bitmap, col + i, row );

            if ( !Color.AreClose( pixelColor, Color.FromArgb( 255, 0, 0, 0 ) ) )
            {
               _textTextureMap[_textTextureMap.Count - 1] |= (byte)( 1 << ( 8 - i ) );
            }
         }
      }
   }
}

void LoadWorldTextureMap( BitmapSource bitmap )
{
   if ( _worldTextureMap is null )
   {
      throw new Exception( "Somehow the world texture map is null, no idea how it happened." );
   }

   // TODO: auto-generate a #define with the number of available textures
   for ( int row = 0; row < bitmap.PixelHeight; row++ )
   {
      for ( int col = 0; col < bitmap.PixelWidth; col++ )
      {
         var pixelColor = GetPixelColor16( bitmap, col, row );
         _worldTextureMap.Add( (byte)PaletteIndexFromColor( pixelColor ) );
      }
   }
}

void LoadPlayerTextureMap( BitmapSource bitmap )
{
   if ( _playerTextureMap is null )
   {
      throw new Exception( "Somehow the player texture map is null, no idea how it happened." );
   }

   for ( int row = 0; row < bitmap.PixelHeight; row++ )
   {
      for ( int col = 0; col < bitmap.PixelWidth; col++ )
      {
         var pixelColor = GetPixelColor16( bitmap, col, row );
         _playerTextureMap.Add( (byte)PaletteIndexFromColor( pixelColor ) );
      }
   }
}

string BuildPaletteAndTexturesOutputString()
{
   if ( _palette is null )
   {
      throw new Exception( "Somehow the palette is null, I have no idea what could have happened." );
   }
   else if ( _textTextureMap is null )
   {
      throw new Exception( "Somehow the text texture map is null, I have no idea what went wrong." );
   }
   else if ( _worldTextureMap is null )
   {
      throw new Exception( "Somehow the world texture map is null, I have no idea what went wrong." );
   }
   else if ( _playerTextureMap is null )
   {
      throw new Exception( "Somehow the player texture map is null, I have no idea what went wrong." );
   }

   string outputString = string.Empty;

   for( int i = 0; i < 16; i++ )
   {
      if ( i < _palette.Count )
      {
         outputString += string.Format( "  zGame.palette[{0}] = 0x{1};\n", i, _palette[i].ToString( "X4" ) );
      }
      else
      {
         outputString += string.Format( "  zGame.palette[{0}] = 0x0000;\n", i );
      }
   }

   outputString += "\n";

   for ( int i = 0; i < _textTextureMap.Count; i++ )
   {
      outputString += string.Format( "  zGame.textTextureMap[{0}] = 0x{1};\n", i, _textTextureMap[i].ToString( "X2" ) );
   }

   outputString += "\n";

   for ( int i = 0, idx = 0; i < _worldTextureMap.Count; i++, idx++ )
   {
      var unpackedPixel1 = (ushort)_worldTextureMap[i++];
      var unpackedPixel2 = (ushort)_worldTextureMap[i];
      var packedPixels = (ushort)( ( unpackedPixel1 << 4 ) | unpackedPixel2 );
      outputString += string.Format( "  zGame.worldTextureMap[{0}] = 0x{1};\n", idx, packedPixels.ToString( "X2" ) );
   }

   outputString += "\n";

   for ( int i = 0, idx = 0; i < _playerTextureMap.Count; i++, idx++ )
   {
      var unpackedPixel1 = (ushort)_playerTextureMap[i++];
      var unpackedPixel2 = (ushort)_playerTextureMap[i];
      var packedPixels = (ushort)( ( unpackedPixel1 << 4 ) | unpackedPixel2 );

      outputString += string.Format( "  zGame.playerTextureMap[{0}] = 0x{1};\n", idx, packedPixels.ToString( "X2" ) );
   }

   return outputString;
}

string GenerateTextureMaps()
{
   var textFileStream = new FileStream( "text_texture_map.png", FileMode.Open, FileAccess.Read, FileShare.Read );
   var textDecoder = new PngBitmapDecoder( textFileStream, BitmapCreateOptions.PreservePixelFormat, BitmapCacheOption.Default );
   BitmapSource textBitmap = textDecoder.Frames[0];
   BitmapSanityCheck( textBitmap );
   LoadTextTextureMap( textBitmap );

   var worldFileStream = new FileStream( "world_texture_map.png", FileMode.Open, FileAccess.Read, FileShare.Read );
   var worldDecoder = new PngBitmapDecoder( worldFileStream, BitmapCreateOptions.PreservePixelFormat, BitmapCacheOption.Default );
   BitmapSource worldBitmap = worldDecoder.Frames[0];
   BitmapSanityCheck( worldBitmap );
   LoadWorldTextureMap( worldBitmap );

   var playerFileStream = new FileStream( "player_texture_map.png", FileMode.Open, FileAccess.Read, FileShare.Read );
   var playerDecoder = new PngBitmapDecoder( playerFileStream, BitmapCreateOptions.PreservePixelFormat, BitmapCacheOption.Default );
   BitmapSource playerBitmap = playerDecoder.Frames[0];
   BitmapSanityCheck( playerBitmap );
   LoadPlayerTextureMap( playerBitmap );

   return BuildPaletteAndTexturesOutputString();
}

string BuildLoadMapFunctionOutputString()
{
   string outputString = "  // only two sections for now\n";

   for( int i = 0; i < 2; i++ )
   {
      if ( i == 0 )
      {
         outputString += string.Format( "  if ( zGame.worldCoords.x == {0} )\n", i );
      }
      else
      {
         outputString += string.Format( "  else if ( zGame.worldCoords.x == {0} )\n", i );
      }

      outputString += "  {\n";

      for ( int row = 0; row < 11; row++ )
      {
         for ( int col = 0; col < 16; col++ )
         {
            int j = ( row * 16 ) + col;

            outputString += string.Format( "    zGame.worldTiles[{0}].textureIndex = {1};\n", j,
               i == 0 ? _worldMapTextureIndexes0[j] : _worldMapTextureIndexes1[j] );
         }
      }

      outputString += "\n";

      for ( int row = 0; row < 22; row++ )
      {
         for ( int col = 0; col < 32; col++ )
         {
            int j = ( row * 32 ) + col;

            outputString += string.Format( "    zGame.collisionTiles[{0}].passable = {1};\n", j,
               i == 0 ? ( _collisionMapPassable0[j] == 1 ? "zTrue" : "zFalse" ) : ( _collisionMapPassable1[j] == 1 ? "zTrue" : "zFalse" ) );
         }
      }

      outputString += "  }\n";
   }

   return outputString;
}

try
{
   string outputString = "/* This file was generated from TextureGenerator, please do not edit */\n\n";
   outputString += "#include \"game.h\"\n\n";
   outputString += "void zGame_LoadData()\n";
   outputString += "{\n";

   Console.Write( "Generating palette and texture maps..." );
   outputString += GenerateTextureMaps();
   Console.Write( "Done!\n" );

   outputString += "}\n\n";
   outputString += "void zGame_LoadWorldMap()\n";
   outputString += "{\n";

   Console.Write( "Generating map loader function..." );
   outputString += BuildLoadMapFunctionOutputString();
   Console.Write( "Done!\n\n" );

   outputString += "}\n";

   File.WriteAllText( "data_loader.c", outputString );

   Console.WriteLine( "The files data_loader.c has been generated, replace" );
   Console.WriteLine( "the existing file in the Zelduino folder. Bye!" );
}
catch( Exception e )
{
   Console.WriteLine( "\n\nUh-oh, something went wrong: " + e.Message + "\n" );
}
