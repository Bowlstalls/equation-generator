using System;
using System.Runtime.InteropServices;

namespace csharp;

public struct Equation {
  public string Str;
  public float[] Roots;
  public float Score;

  internal unsafe Equation(Native.EqEquation src)
  {
    Str = Marshal.PtrToStringAnsi((IntPtr)src.str);
    Roots = new float[src.root_count];
    Score = src.score;
    for (nuint i = 0; i < src.root_count; i++) {
      Roots[i] = src.roots[i];
    }
  }
}