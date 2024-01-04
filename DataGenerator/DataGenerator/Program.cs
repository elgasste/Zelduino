﻿using System.IO;
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

void LoadWorldTextureMap( BitmapSource bitmap )
{
   if ( _worldTextureMap is null )
   {
      throw new Exception( "Somehow the world texture map is null, no idea how it happened." );
   }

   for ( int row = 0; row < bitmap.PixelHeight; row++ )
   {
      for ( int col = 0; col < bitmap.PixelWidth; col++ )
      {
         var pixelColor = GetPixelColor( bitmap, col, row );
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
         var pixelColor = GetPixelColor( bitmap, col, row );
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

   for ( int i = 0, idx = 0; i < _worldTextureMap.Count; i++, idx++ )
   {
      var unpackedPixel1 = _worldTextureMap[i++];
      var unpackedPixel2 = _worldTextureMap[i];
      byte packedPixels = (byte)( ( unpackedPixel1 << 2 ) | unpackedPixel2 );
      outputString += string.Format( "  zGame.worldTextureMap[{0}] = 0x{1};\n", idx, packedPixels.ToString( "X2" ) );
   }

   outputString += "\n";

   for ( int i = 0, idx = 0; i < _playerTextureMap.Count; i++, idx++ )
   {
      var unpackedPixel1 = _playerTextureMap[i++];
      var unpackedPixel2 = _playerTextureMap[i];
      byte packedPixels = (byte)( ( unpackedPixel1 << 2 ) | unpackedPixel2 );
      outputString += string.Format( "  zGame.playerTextureMap[{0}] = 0x{1};\n", idx, packedPixels.ToString( "X2" ) );
   }

   return outputString;
}

string GenerateTextureMaps()
{
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

string BuildWorldTileMapOutputString()
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

   Console.Write( "Generating palette and texture maps..." );
   outputString += GenerateTextureMaps();
   Console.Write( "Done!\n" );

   Console.Write( "Generating world tile map..." );
   outputString += BuildWorldTileMapOutputString();
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
