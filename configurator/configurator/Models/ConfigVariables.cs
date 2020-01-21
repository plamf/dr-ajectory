namespace configurator.Models
{
    public class ConfigVariables
    {
        public string IboRating { get; set; }
        public string WeightOnBowstring { get; set; }
        public string LbsOfForce { get; set; }
        public string DrawLength { get; set; }
        public string ArrowWeight { get; set; }
        public string PayLoad => $"<{IboRating},{WeightOnBowstring},{LbsOfForce},{DrawLength},{ArrowWeight}>";
    }
}