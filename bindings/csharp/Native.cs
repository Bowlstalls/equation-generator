using System.Runtime.InteropServices;

namespace csharp {
  internal static unsafe class Native
  {
    [StructLayout(LayoutKind.Sequential)]
    internal struct EqValueSettingsItem
    {
      internal int max;
      internal float low_bias;
      internal float negative_chance;
    }

    [StructLayout(LayoutKind.Sequential)]
    internal struct EqValueSettings
    {
      internal float @base;
      internal EqValueSettingsItem values;
      internal EqValueSettingsItem roots;
      internal EqValueSettingsItem powers;
    }
    
    [StructLayout(LayoutKind.Sequential)]
    internal struct EqOperationWeights {
      internal int add;
      internal int mult;
    }

    [StructLayout(LayoutKind.Sequential)]
    internal struct EqStructureSettings {
      internal int max_depth;
      internal int max_width;
      internal float value_chance;
      internal float right_side_chance;
      internal EqOperationWeights operation_weights;
    }
    
    [StructLayout(LayoutKind.Sequential)]
    internal struct EqSettings
    {
      internal uint seed;
      internal byte* variable_name;
      internal int degree;
      internal EqValueSettings value_settings;
      internal EqStructureSettings structure_settings;
    }
    
    [StructLayout(LayoutKind.Sequential)]
    internal struct EqEquation
    {
      internal byte* str;
      internal float* roots;
      internal nuint root_count;
      internal float score;
    }

    internal struct EqGenerator {}

    [DllImport("equation_generator")]
    internal static extern EqGenerator* eq_generator_create(EqSettings* settings);
    [DllImport("equation_generator")]
    internal static extern void eq_generator_destroy(EqGenerator* generator);
    
    [DllImport("equation_generator")]
    internal static extern void eq_generator_generate(EqGenerator* generator, EqEquation* equation);
    [DllImport("equation_generator")]
    internal static extern void eq_equation_destroy(EqEquation* equation);
  }
}
