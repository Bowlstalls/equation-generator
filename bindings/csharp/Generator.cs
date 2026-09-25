using System;
using System.Runtime.InteropServices;
using System.Text;

namespace csharp {
  internal sealed unsafe class GeneratorHandle : SafeHandle
  {
    public override bool IsInvalid => handle == IntPtr.Zero;

    public GeneratorHandle(Settings settings) : base(IntPtr.Zero, true)
    {
      var bytes = Encoding.UTF8.GetBytes(settings.VariableName + '\0');
      fixed (byte* variableName = bytes) {
        var nativeSettings = Conversions.ConvertSettings(settings, variableName);
        var generator = Native.eq_generator_create(&nativeSettings);
        SetHandle((IntPtr)generator);
      }
    }
    
    protected override bool ReleaseHandle()
    {
      Native.eq_generator_destroy((Native.EqGenerator*)handle);
      return true;
    }
    
    public Equation Generate()
    {
      var res = new Native.EqEquation();
      Native.eq_generator_generate((Native.EqGenerator*)handle, &res);
      try {
        return Conversions.ConvertEquation(res);
      } finally {
        Native.eq_equation_destroy(&res);
      }
    }
  }
  
  public class Generator(Settings settings) {
    private GeneratorHandle _handle = new(settings);
    public Settings Settings
    {
      get;
      set
      {
        field = value;
        _handle = new GeneratorHandle(field);
      }
    }

    public Equation Generate() => _handle.Generate();
  }
}