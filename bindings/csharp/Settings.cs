using System;
using System.Runtime.InteropServices;
using System.Text;

namespace csharp {
  public struct ValueSettings {
    public struct Item()
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
      
      internal Native.EqValueSettingsItem Native = new();
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
    
    internal Native.EqValueSettings Native = new();

    public ValueSettings()
    {
      Base = 1;
      Values = new Item{Max = 20, LowBias = 2, NegativeChance = 0.3f};
      Roots = new Item{Max = 10, LowBias = 1, NegativeChance = 0.3f};
      Powers = new Item{Max = 2, LowBias = 1, NegativeChance = 0};
    }
  }

  public struct StructureSettings
  {
    public struct OperationWeightsType()
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

      internal Native.EqOperationWeights Native = new();
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

    internal Native.EqStructureSettings Native = new();
    
    public StructureSettings()
    {
      MaxDepth = 3;
      MaxWidth = 4;
      ValueChance = 0.3f;
      RightSideChance = 0.2f;
      OperationWeights = new OperationWeightsType{Add = 2, Mult = 2};
    }
  }

  public unsafe class Settings {
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

    public Settings()
    {
      Seed = (uint)Guid.NewGuid().GetHashCode();
      VariableName = "x";
      Degree = 2;
      ValueSettings = new ValueSettings();
      StructureSettings = new StructureSettings();
    }

    ~Settings()
    {
      Marshal.FreeHGlobal((IntPtr)Native.variable_name);
    }
  }
}
