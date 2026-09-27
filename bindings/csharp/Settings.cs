using System;
using System.Runtime.InteropServices;
using System.Text;

namespace csharp {
  public struct ValueSettings
  {
    public struct Item
    {
      public int Max
      {
        get;
        set
        {
          field = value;
          Native.max = value;
        }
      }
      public float LowBias
      {
        get;
        set
        {
          field = value;
          Native.low_bias = value;
        }
      }
      public float NegativeChance
      {
        get;
        set
        {
          field = value;
          Native.negative_chance = value;
        }
      }
      
      internal Native.EqValueSettingsItem Native;
    }
    
    public float Base
    {
      get;
      set
      {
        field = value;
        Native.@base = value;
      }
    }
    public Item Values
    {
      get;
      set
      {
        field = value;
        Native.values = value.Native;
      }
    }
    public Item Roots
    {
      get;
      set
      {
        field = value;
        Native.roots = value.Native;
      }
    }
    public Item Powers
    {
      get;
      set
      {
        field = value;
        Native.powers = value.Native;
      }
    }
    
    internal Native.EqValueSettings Native;
  }

  public struct StructureSettings
  {
    public struct OperationWeightsType
    {
      public int Add
      {
        get;
        set
        {
          field = value;
          Native.add = value;
        }
      }
      public int Mult
      {
        get;
        set
        {
          field = value;
          Native.mult = value;
        }
      }

      internal Native.EqOperationWeights Native;
    }

    public int MaxDepth
    {
      get;
      set
      {
        field = value;
        Native.max_depth = value;
      }
    }
    public int MaxWidth
    {
      get;
      set
      {
        field = value;
        Native.max_width = value;
      }
    }
    public float ValueChance
    {
      get;
      set
      {
        field = value;
        Native.value_chance = value;
      }
    }
    public float RightSideChance
    {
      get;
      set
      {
        field = value;
        Native.right_side_chance = value;
      }
    }
    public OperationWeightsType OperationWeights
    {
      get;
      set
      {
        field = value;
        Native.operation_weights = value.Native;
      }
    }

    internal Native.EqStructureSettings Native;
  }

  public unsafe class Settings
  {
    public uint Seed
    {
      get;
      set
      {
        field = value;
        Native.seed = value;
      }
    }
    public string VariableName
    {
      get;
      set
      {
        field = value;
        if (Native.variable_name != null) {
          Marshal.FreeHGlobal((IntPtr)Native.variable_name);
        }
        var bytes = Encoding.UTF8.GetBytes(value);
        Native.variable_name = (byte*)Marshal.AllocHGlobal(bytes.Length);
        Marshal.Copy(bytes, 0, (IntPtr)Native.variable_name, bytes.Length);
        Native.variable_name![bytes.Length] = 0;
      }
    }
    public int Degree
    {
      get;
      set
      {
        field = value;
        Native.degree = value;
      }
    }
    public ValueSettings ValueSettings
    {
      get;
      set
      {
        field = value;
        Native.value_settings = value.Native;
      }
    }
    public StructureSettings StructureSettings
    {
      get;
      set
      {
        field = value;
        Native.structure_settings = value.Native;
      }
    }

    internal Native.EqSettings Native;

    ~Settings()
    {
      Marshal.FreeHGlobal((IntPtr)Native.variable_name);
    }
  }
}
