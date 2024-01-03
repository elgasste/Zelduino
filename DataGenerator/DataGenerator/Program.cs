using System.IO;
using System.Windows.Media;
using System.Windows;
using System.Windows.Media.Imaging;

int[] _worldMapTextureIndexes =
{
   2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,
   2,2,2,2,1,2,3,0,0,2,2,2,2,2,2,2,
   2,2,2,3,0,0,0,0,0,2,2,2,2,2,2,2,
   2,2,3,0,0,0,0,0,0,2,2,2,2,2,2,2,
   2,3,0,0,0,0,0,0,0,2,2,2,2,2,2,2,
   0,0,0,0,0,0,0,0,0,4,2,2,2,2,2,2,
   2,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   2,2,0,0,0,0,0,0,0,0,0,0,0,0,6,6,
   2,2,0,0,0,0,0,0,0,0,0,0,0,0,2,2,
   2,2,6,6,6,6,6,6,6,6,6,6,6,6,2,2,
   2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2
};

int[] _worldMapPassable =
{
   0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,
   0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,0,
   0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,
   0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,
   0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,
   1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,
   0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
   0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
   0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

var _palette = new List<UInt16>();
var _textureMap = new List<byte>();

Console.WriteLine();
Console.WriteLine( "=====================================================" );
Console.WriteLine( "               ZELDUINO DATA GENERATOR" );
Console.WriteLine( "=====================================================" );
Console.WriteLine();

static void BitmapSanityCheck( BitmapSource bitmap )
{
   if ( bitmap.Format != PixelFormats.Indexed8 )
   {
      throw new Exception( "Expecting image pixel format to be Indexed8" );
   }
   else if ( bitmap.Palette.Colors.Count > 15 )
   {
      throw new Exception( "Too many colors found in image palette" );
   }
   else if ( bitmap.PixelWidth <= 0 || bitmap.PixelWidth % 16 != 0 )
   {
      throw new Exception( "Image width should be a multiple of 16" );
   }
   else if ( bitmap.PixelHeight != 16 )
   {
      throw new Exception( "Image height should be exactly 16" );
   }
}

static UInt16 ColortoUInt16( Color color )
{
   var r16 = (UInt16)( ( color.R / 255.0 ) * 31 );
   var g16 = (UInt16)( ( color.G / 255.0 ) * 63 );
   var b16 = (UInt16)( ( color.B / 255.0 ) * 31 );

   return (UInt16)( ( r16 << 11 ) | ( g16 << 5 ) | b16 );
}

static UInt16 GetPixelColor( BitmapSource bitmap, int x, int y )
{
   var bytesPerPixel = (int)Math.Truncate( ( bitmap.Format.BitsPerPixel + 7.0) / 8.0);
   int stride = bitmap.PixelWidth * bytesPerPixel;
   byte[] pixel = new byte[1];
   var rect = new Int32Rect( x, y, 1, 1 );

   bitmap.CopyPixels( rect, pixel, stride, 0 );
   var color = bitmap.Palette.Colors[pixel[0]];
   return ColortoUInt16( color );
}

int PaletteIndexFromColor( UInt16 color )
{
   if ( _palette is null )
   {
      return 0;
   }

   int paletteIndex = _palette.IndexOf( color );

   if ( paletteIndex < 0 )
   {
      _palette.Add( color );
      paletteIndex = _palette.Count - 1;
   }

   return paletteIndex;
}

void LoadTextureMap( BitmapSource bitmap )
{
   if ( _textureMap is null )
   {
      throw new Exception( "Somehow the texture map is null, no idea how it happened." );
   }

   for ( int row = 0; row < bitmap.PixelHeight; row++ )
   {
      for ( int col = 0; col < bitmap.PixelWidth; col++ )
      {
         var pixelColor = GetPixelColor( bitmap, col, row );
         _textureMap.Add( (byte)PaletteIndexFromColor(pixelColor) );
      }
   }
}

string BuildTexturesOutputString( BitmapSource bitmap )
{
   if ( _palette is null )
   {
      throw new Exception( "Somehow the palette is null, I have no idea what could have happened." );
   }
   else if ( _textureMap is null )
   {
      throw new Exception( "Somehow the texture map is null, I have no idea what went wrong." );
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

   for ( int i = 0, idx = 0; i < _textureMap.Count; i++, idx++ )
   {
      var unpackedPixel1 = _textureMap[i++];
      var unpackedPixel2 = _textureMap[i];
      byte packedPixels = (byte)( ( unpackedPixel1 << 2 ) | unpackedPixel2 );
      outputString += string.Format( "  zGame.worldTextureMap[{0}] = 0x{1};\n", idx, packedPixels.ToString( "X2" ) );
   }

   return outputString;
}

string GeneratePaletteAndTextures()
{
   var textureMapStream = new FileStream( "texture_map.png", FileMode.Open, FileAccess.Read, FileShare.Read );
   var decoder = new PngBitmapDecoder( textureMapStream, BitmapCreateOptions.PreservePixelFormat, BitmapCacheOption.Default );
   BitmapSource bitmap = decoder.Frames[0];
   BitmapSanityCheck( bitmap );
   LoadTextureMap( bitmap );
   return BuildTexturesOutputString( bitmap );
}

string BuildWorldOutputString()
{
   string outputString = "\n";

   for( int row = 0; row < 11; row++ )
   {
      for( int col = 0; col < 16; col++ )
      {
         int i = ( row * 16 ) + col;

         outputString += string.Format( "  zGame.worldTiles[{0}].textureIndex = {1};\n", i, _worldMapTextureIndexes[i]);
         outputString += string.Format( "  zGame.worldTiles[{0}].passable = {1};\n", i, _worldMapPassable[i] == 1 ? "zTrue" : "zFalse" );
      }
   }

   return outputString;
}

try
{
   string outputString = "/* This file was generated from TextureGenerator, please do not edit */\n\n";
   outputString += "#include \"game.h\"\n\n";
   outputString += "void zGame_LoadData()\n";
   outputString += "{\n";

   Console.Write("Generating pallette and texture map...");
   outputString += GeneratePaletteAndTextures();
   Console.Write("Done!\n");

   Console.Write( "Generating world map..." );
   outputString += BuildWorldOutputString();
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
