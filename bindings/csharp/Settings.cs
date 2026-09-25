namespace csharp {
  public struct ValueSettings
  {
    public struct Item
    {
      public int Max;
      public float LowBias;
      public float NegativeChance;
    }
    
    public float Base;
    public Item Values;
    public Item Roots;
    public Item Powers;
  }

  public struct StructureSettings
  {
    public struct OperationWeightsType
    {
      public int Add;
      public int Mult;
    }

    public int MaxDepth;
    public int MaxWidth;
    public float ValueChance;
    public float RightSideChance;
    public OperationWeightsType OperationWeights;
  }

  public struct Settings
  {
    public uint Seed;
    public string VariableName;
    public int Degree;
    public ValueSettings ValueSettings;
    public StructureSettings StructureSettings;
  }
}