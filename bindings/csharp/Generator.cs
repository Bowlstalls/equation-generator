namespace csharp {
  public unsafe class Generator(Settings settings) {
    public Settings Settings = settings;
    
    public Equation Generate()
    {
      var res = new Native.EqEquation();
      fixed (Native.EqSettings* nativeSettings = &Settings.Native)
      {
        var generator = Native.eq_generator_create(nativeSettings);
        Native.eq_generator_generate(generator, &res);
        try {
          return new Equation(res);
        } finally {
          Native.eq_generator_destroy(generator);
          Native.eq_equation_destroy(&res);
        }
      }
    }
  }
}