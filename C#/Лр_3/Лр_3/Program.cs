using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;

public enum Frequency
{
    Weekly,
    Monthly,
    Yearly
}

interface IRateAndCopy : IComparable<Article>
{
    double Rating { get; }
    object DeepCopy();
}

class Person : IRateAndCopy
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

    public override bool Equals(object obj)
    {
        if (obj == null || GetType() != obj.GetType())
            return false;

        Person other = (Person)obj;
        return FirstName == other.FirstName &&
               LastName == other.LastName &&
               DateOfBirth == other.DateOfBirth;
    }

    public override int GetHashCode()
    {
        return HashCode.Combine(FirstName, LastName, DateOfBirth);
    }

    public static bool operator ==(Person person1, Person person2)
    {
        if (ReferenceEquals(person1, person2))
            return true;
        if (person1 is null || person2 is null)
            return false;
        return person1.Equals(person2);
    }

    public static bool operator !=(Person person1, Person person2)
    {
        return !(person1 == person2);
    }

    public object DeepCopy()
    {
        return new Person(FirstName, LastName, DateOfBirth);
    }

    public override string ToString()
    {
        return $"{FirstName} {LastName}, Date of Birth: {DateOfBirth.ToShortDateString()}";
    }

    public string ToShortString()
    {
        return $"{FirstName} {LastName}";
    }

    public double Rating => throw new NotImplementedException();

    public int CompareTo(Article other)
    {
        if (other == null) return 1;
        return this.LastName.CompareTo(other.Author.LastName);


    }
}

class Article : IRateAndCopy
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

    public object DeepCopy()
    {
        return new Article((Person)Author.DeepCopy(), Title, Rating);
    }

    public int CompareTo(Article other)
    {
        if (other == null) return 1;
        return this.Author.LastName.CompareTo(other.Author.LastName);
    }
}

class Edition : IComparable<Edition>
{
    protected string editionName;
    protected DateTime releaseDate;
    protected int circulation;

    public Edition(string name, DateTime date, int circulation)
    {
        editionName = name;
        releaseDate = date;
        Circulation = circulation;
    }

    public Edition()
    {
        editionName = "Unknown";
        releaseDate = DateTime.Now;
        Circulation = 0;
    }

    public string EditionName
    {
        get { return editionName; }
        set { editionName = value; }
    }

    public DateTime ReleaseDate
    {
        get { return releaseDate; }
        set { releaseDate = value; }
    }

    public int Circulation
    {
        get { return circulation; }
        set
        {
            if (value < 0)
                throw new ArgumentException("Circulation value cannot be negative.");
            circulation = value;
        }
    }

    public virtual object DeepCopy()
    {
        return new Edition(editionName, releaseDate, circulation);
    }

    public override bool Equals(object obj)
    {
        if (obj == null || GetType() != obj.GetType())
            return false;

        Edition other = (Edition)obj;
        return editionName == other.editionName &&
               releaseDate == other.releaseDate &&
               circulation == other.circulation;
    }

    public override int GetHashCode()
    {
        return HashCode.Combine(editionName, releaseDate, circulation);
    }

    public int CompareTo(Edition other)
    {
        if (other == null) return 1;
        return this.ReleaseDate.CompareTo(other.ReleaseDate);
    }

    public override string ToString()
    {
        return $"Edition Name: {editionName}, Release Date: {releaseDate.ToShortDateString()}, Circulation: {circulation}";
    }
}

class Magazine : Edition
{
    private Frequency releaseFrequency;
    private List<Person> editors;
    private List<Article> articles;

    public Magazine(string name, Frequency frequency, DateTime date, int circulation) : base(name, date, circulation)
    {
        releaseFrequency = frequency;
        editors = new List<Person>();
        articles = new List<Article>();
    }

    public double Rating
    {
        get
        {
            if (articles.Count == 0)
                return 0;

            double sum = 0;
            foreach (Article article in articles)
            {
                sum += article.Rating;
            }
            return sum / articles.Count;
        }
    }

    public List<Article> GetArticlesByTitleSubstring(string titleSubstring)
    {
        return articles.Where(article => article.Title.Contains(titleSubstring)).ToList();
    }

    public List<Article> Articles => articles;

    public List<Person> Editors => editors;

    public void AddArticles(params Article[] newArticles)
    {
        articles.AddRange(newArticles);
    }

    public void AddEditors(params Person[] newEditors)
    {
        editors.AddRange(newEditors);
    }

    public override object DeepCopy()
    {
        Magazine copiedMagazine = new Magazine(editionName, releaseFrequency, releaseDate, circulation);
        copiedMagazine.editors.AddRange(editors.Select(editor => (Person)editor.DeepCopy()));
        copiedMagazine.articles.AddRange(articles.Select(article => (Article)article.DeepCopy()));
        return copiedMagazine;
    }

    public override bool Equals(object obj)
    {
        if (obj == null || GetType() != obj.GetType())
            return false;

        Magazine other = (Magazine)obj;
        return base.Equals(obj) &&
               releaseFrequency == other.releaseFrequency &&
               Enumerable.SequenceEqual(editors, other.editors) &&
               Enumerable.SequenceEqual(articles, other.articles);
    }

    public override int GetHashCode()
    {
        unchecked
        {
            int hash = 17;
            hash = hash * 23 + base.GetHashCode();
            hash = hash * 23 + releaseFrequency.GetHashCode();
            foreach (Person editor in editors)
            {
                hash = hash * 23 + editor.GetHashCode();
            }
            foreach (Article article in articles)
            {
                hash = hash * 23 + article.GetHashCode();
            }
            return hash;
        }
    }

    public override string ToString()
    {
        string result = base.ToString() + $", Release Frequency: {releaseFrequency}\nEditors:\n";
        foreach (Person editor in editors)
        {
            result += $"{editor}\n";
        }
        result += "Articles:\n";
        foreach (Article article in articles)
        {
            result += $"{article}\n";
        }
        return result;
    }

    public string ToShortString()
    {
        return $"{base.ToString()}, Release Frequency: {releaseFrequency}, Average Rating: {Rating}";
    }
}

class Program
{
    static void Main(string[] args)
    {
        try
        {
            Magazine magazine = new Magazine("Magazine 1", Frequency.Monthly, DateTime.Now, 5000);
            magazine.AddArticles(new Article(new Person("Jane", "Doe", new DateTime(1990, 5, 15)), "Advanced AI", 4.5),
                                 new Article(new Person("John", "Smith", new DateTime(1985, 10, 20)), "Quantum Computing", 4.2));
            magazine.AddEditors(new Person("Editor", "One", new DateTime(1990, 5, 15)), new Person("Editor", "Two", new DateTime(1985, 10, 20)));

            Console.WriteLine("\nMagazine Details:");
            Console.WriteLine(magazine.ToString());

            magazine.Articles.Sort();
            Console.WriteLine("\nSorted Articles by Title:");
            foreach (Article article in magazine.Articles)
            {
                Console.WriteLine(article.Title);
            }

            magazine.Articles.Sort((a1, a2) => a1.Author.LastName.CompareTo(a2.Author.LastName));
            Console.WriteLine("\nSorted Articles by Author's Last Name:");
            foreach (Article article in magazine.Articles)
            {
                Console.WriteLine(article.Title);
            }

            magazine.Articles.Sort((a1, a2) => a2.Rating.CompareTo(a1.Rating));
            Console.WriteLine("\nSorted Articles by Rating:");
            foreach (Article article in magazine.Articles)
            {
                Console.WriteLine(article.Title);
            }

        }
        catch (ArgumentException ex)
        {
            Console.WriteLine($"ArgumentException: {ex.Message}");
        }
    }
}
