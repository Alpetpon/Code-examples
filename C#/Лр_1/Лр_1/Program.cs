using System;

enum Frequency
{
    Weekly,
    Monthly,
    Yearly
}


class Person
{
    public string FirstName { get; set; }
    public string LastName { get; set; }
    public DateTime DateOfBirth { get; set; }

    public Person(string firstName, string lastName, DateTime dateOfBirth)
    {
        FirstName = firstName;
        LastName = lastName;
        DateOfBirth = dateOfBirth;
    }

    public Person()
    {
        FirstName = "John";
        LastName = "Doe";
        DateOfBirth = DateTime.Now;
    }

    public override string ToString()
    {
        return $"{FirstName} {LastName}, Date of Birth: {DateOfBirth.ToShortDateString()}";
    }

    public string ToShortString()
    {
        return $"{FirstName} {LastName}";
    }
}


class Article
{
    public Person Author { get; set; }
    public string Title { get; set; }
    public double Rating { get; set; }

    public Article(Person author, string title, double rating)
    {
        Author = author;
        Title = title;
        Rating = rating;
    }

    public Article()
    {
        Author = new Person();
        Title = "Untitled";
        Rating = 0.0;
    }

    public override string ToString()
    {
        return $"Author: {Author}, Title: {Title}, Rating: {Rating}";
    }
}


class Magazine
{
    private string magazineName;
    private Frequency releaseFrequency;
    private DateTime releaseDate;
    private int circulation;
    private Article[] articles;

    public Magazine(string name, Frequency frequency, DateTime date, int circulation)
    {
        magazineName = name;
        releaseFrequency = frequency;
        releaseDate = date;
        this.circulation = circulation;
        articles = new Article[0];
    }

    public Magazine()
    {
        magazineName = "Unknown";
        releaseFrequency = Frequency.Monthly;
        releaseDate = DateTime.Now;
        circulation = 1000;
        articles = new Article[0];
    }

    public string MagazineName
    {
        get { return magazineName; }
        set { magazineName = value; }
    }

    public Frequency ReleaseFrequency
    {
        get { return releaseFrequency; }
        set { releaseFrequency = value; }
    }

    public DateTime ReleaseDate
    {
        get { return releaseDate; }
        set { releaseDate = value; }
    }

    public int Circulation
    {
        get { return circulation; }
        set { circulation = value; }
    }

    public Article[] Articles
    {
        get { return articles; }
        set { articles = value; }
    }

    public double AverageRating
    {
        get
        {
            if (articles.Length == 0)
                return 0;

            double sum = 0;
            foreach (Article article in articles)
            {
                sum += article.Rating;
            }
            return sum / articles.Length;
        }
    }

    public bool this[Frequency frequency]
    {
        get { return releaseFrequency == frequency; }
    }

    public void AddArticles(params Article[] newArticles)
    {
        int oldLength = articles.Length;
        Array.Resize(ref articles, oldLength + newArticles.Length);
        for (int i = 0; i < newArticles.Length; i++)
        {
            articles[oldLength + i] = newArticles[i];
        }
    }

    public override string ToString()
    {
        string result = $"Magazine: {magazineName}, Frequency: {releaseFrequency}, Release Date: {releaseDate.ToShortDateString()}, Circulation: {circulation}\nArticles:\n";
        foreach (Article article in articles)
        {
            result += $"{article}\n";
        }
        return result;
    }

    public string ToShortString()
    {
        return $"Magazine: {magazineName}, Frequency: {releaseFrequency}, Release Date: {releaseDate.ToShortDateString()}, Circulation: {circulation}, Average Rating: {AverageRating}";
    }
}

class Program
{
    static void Main(string[] args)
    {
        Magazine magazine = new Magazine();
        Console.WriteLine("Magazine Details:");
        Console.WriteLine(magazine.ToShortString());

        Console.WriteLine($"Frequency.Weekly: {magazine[Frequency.Weekly]}");
        Console.WriteLine($"Frequency.Monthly: {magazine[Frequency.Monthly]}");
        Console.WriteLine($"Frequency.Yearly: {magazine[Frequency.Yearly]}");

        magazine.MagazineName = "Tech Review";
        magazine.ReleaseFrequency = Frequency.Monthly;
        magazine.ReleaseDate = new DateTime(2024, 3, 1);
        magazine.Circulation = 5000;
        Console.WriteLine("\nMagazine Details After Modification:");
        Console.WriteLine(magazine.ToString());

        magazine.AddArticles(new Article(new Person("Jane", "Doe", new DateTime(1990, 5, 15)), "Advanced AI", 4.5),
                             new Article(new Person("John", "Smith", new DateTime(1985, 10, 20)), "Quantum Computing", 4.2));
        Console.WriteLine("\nMagazine Details After Adding Articles:");
        Console.WriteLine(magazine.ToString());

        CompareArrayPerformance();
    }

    static void CompareArrayPerformance()
    {
        const int nrow = 1000;
        const int ncolumn = 1000;

        Article[] oneDimensionalArray = new Article[nrow * ncolumn];
        for (int i = 0; i < oneDimensionalArray.Length; i++)
        {
            oneDimensionalArray[i] = new Article();
        }

        Article[,] rectangularArray = new Article[nrow, ncolumn];
        for (int i = 0; i < nrow; i++)
        {
            for (int j = 0; j < ncolumn; j++)
            {
                rectangularArray[i, j] = new Article();
            }
        }

        Article[][] jaggedArray = new Article[nrow][];
        for (int i = 0; i < nrow; i++)
        {
            jaggedArray[i] = new Article[ncolumn];
            for (int j = 0; j < ncolumn; j++)
            {
                jaggedArray[i][j] = new Article();
            }
        }

        System.Diagnostics.Stopwatch stopwatch = System.Diagnostics.Stopwatch.StartNew();


        stopwatch.Stop();
        Console.WriteLine($"\nTime taken for operations with 1D array: {stopwatch.ElapsedMilliseconds} ms");


        stopwatch.Restart();

        stopwatch.Stop();
        Console.WriteLine($"Time taken for operations with 2D rectangular array: {stopwatch.ElapsedMilliseconds} ms");

        stopwatch.Restart();

        stopwatch.Stop();
        Console.WriteLine($"Time taken for operations with 2D jagged array: {stopwatch.ElapsedMilliseconds} ms");
    }
}
