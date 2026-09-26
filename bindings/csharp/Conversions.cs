using System;
using System.Runtime.InteropServices;

namespace csharp {
  internal static unsafe class Conversions {
    internal static Native.EqSettings ConvertSettings(Settings src, byte* variableName)
    {
      return new Native.EqSettings {
        seed = src.Seed,
        variable_name = variableName,
        degree = src.Degree,
        value_settings = ConvertValueSettings(src.ValueSettings),
        structure_settings = ConvertStructureSettings(src.StructureSettings)
      };

      Native.EqValueSettings ConvertValueSettings(ValueSettings valSrc)
      {
        return new Native.EqValueSettings {
          @base = valSrc.Base,
          values = ConvertItem(valSrc.Values),
          roots = ConvertItem(valSrc.Roots),
          powers = ConvertItem(valSrc.Powers),
        };
        
        Native.EqValueSettingsItem ConvertItem(ValueSettings.Item itemSrc)
        {
          return new Native.EqValueSettingsItem {
            max = itemSrc.Max,
            low_bias = itemSrc.LowBias,
            negative_chance = itemSrc.NegativeChance
          };
        }
      }
      
      Native.EqStructureSettings ConvertStructureSettings(StructureSettings strSrc)
      {
        return new Native.EqStructureSettings {
          max_depth = strSrc.MaxDepth,
          max_width = strSrc.MaxWidth,
          value_chance = strSrc.ValueChance,
          right_side_chance = strSrc.RightSideChance,
          operation_weights = new Native.EqOperationWeights {
            add = strSrc.OperationWeights.Add,
            mult = strSrc.OperationWeights.Mult
          }
        };
      }
    }

    internal static Equation ConvertEquation(Native.EqEquation src)
    {
      var res = new Equation {
        Str = Marshal.PtrToStringAnsi((IntPtr)src.str),
        Roots = new float[src.root_count],
        Score = src.score
      };
      for (nuint i = 0; i < src.root_count; i++) {
        res.Roots[i] = src.roots[i];
      }
      return res;
    }
  }
}