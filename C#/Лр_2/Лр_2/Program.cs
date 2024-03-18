using System;
using System.Collections;

public enum Frequency
{
    Weekly,
    Monthly,
    Yearly
}


interface IRateAndCopy
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

    public double Rating => throw new NotImplementedException(); // Implement if needed
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
}

class Edition
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

    public override string ToString()
    {
        return $"Edition Name: {editionName}, Release Date: {releaseDate.ToShortDateString()}, Circulation: {circulation}";
    }
}

class Magazine : Edition, IRateAndCopy
{
    private Frequency releaseFrequency;
    private ArrayList editors;
    private ArrayList articles;

    public Magazine(string name, Frequency frequency, DateTime date, int circulation) : base(name, date, circulation)
    {
        releaseFrequency = frequency;
        editors = new ArrayList();
        articles = new ArrayList();
    }

    public Magazine() : base()
    {
        releaseFrequency = Frequency.Monthly;
        editors = new ArrayList();
        articles = new ArrayList();
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

    public IEnumerable<Article> GetArticlesByTitleSubstring(string titleSubstring)
    {
        foreach (Article article in Articles)
        {
            if (article.Title.Contains(titleSubstring))
            {
                yield return article;
            }
        }
    }

    public ArrayList Articles => articles;

    public ArrayList Editors => editors;

    public void AddArticles(params Article[] newArticles)
    {
        foreach (Article article in newArticles)
        {
            articles.Add(article);
        }
    }

    public void AddEditors(params Person[] newEditors)
    {
        foreach (Person editor in newEditors)
        {
            editors.Add(editor);
        }
    }

    public override object DeepCopy()
    {
        Magazine copiedMagazine = new Magazine(editionName, releaseFrequency, releaseDate, circulation);
        foreach (Article article in articles)
        {
            copiedMagazine.AddArticles((Article)article.DeepCopy());
        }
        foreach (Person editor in editors)
        {
            copiedMagazine.AddEditors((Person)editor.DeepCopy());
        }
        return copiedMagazine;
    }

    public override bool Equals(object obj)
    {
        if (obj == null || GetType() != obj.GetType())
            return false;

        Magazine other = (Magazine)obj;
        return base.Equals(obj) &&
               releaseFrequency == other.releaseFrequency &&
               editors.Count == other.editors.Count &&
               articles.Count == other.articles.Count &&
               Enumerable.SequenceEqual(editors.Cast<Person>(), other.editors.Cast<Person>()) &&
               Enumerable.SequenceEqual(articles.Cast<Article>(), other.articles.Cast<Article>());
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

    public IEnumerator GetEnumerator(double ratingThreshold)
    {
        foreach (Article article in articles)
        {
            if (article.Rating > ratingThreshold)
                yield return article;
        }
    }

    public IEnumerator GetEnumerator(string titleSubstring)
    {
        foreach (Article article in articles)
        {
            if (article.Title.Contains(titleSubstring))
                yield return article;
        }
    }
}

class Program
{
    static void Main(string[] args)
    {
        try
        {
            Edition edition1 = new Edition("Edition 1", DateTime.Now, 1000);
            Edition edition2 = new Edition("Edition 1", DateTime.Now, 1000);

            Console.WriteLine($"Edition 1 Hash Code: {edition1.GetHashCode()}");
            Console.WriteLine($"Edition 2 Hash Code: {edition2.GetHashCode()}");

            if (edition1 == edition2)
                Console.WriteLine("Editions are equal.");
            else
                Console.WriteLine("Editions are not equal.");

            Magazine magazine = new Magazine("Magazine 1", Frequency.Monthly, DateTime.Now, 5000);
            magazine.AddArticles(new Article(new Person("Jane", "Doe", new DateTime(1990, 5, 15)), "Advanced AI", 4.5),
                                 new Article(new Person("John", "Smith", new DateTime(1985, 10, 20)), "Quantum Computing", 4.2));
            magazine.AddEditors(new Person("Editor", "One", new DateTime(1990, 5, 15)), new Person("Editor", "Two", new DateTime(1985, 10, 20)));

            Console.WriteLine("\nMagazine Details:");
            Console.WriteLine(magazine.ToString());

            Console.WriteLine($"\nEdition of Magazine: {magazine.EditionName}");

            Magazine copyMagazine = (Magazine)magazine.DeepCopy();

            Console.WriteLine("\nDeep Copy of Magazine:");
            Console.WriteLine(copyMagazine.ToString());

            magazine.EditionName = "Modified Magazine";

            Console.WriteLine("\nModified Magazine:");
            Console.WriteLine(magazine.ToString());

            Console.WriteLine("\nCopied Magazine After Modification:");
            Console.WriteLine(copyMagazine.ToString());

            Console.WriteLine("\nArticles with Rating Above 4.3:");
            foreach (Article article in magazine.Articles)
            {
                if (article.Rating > 4.3)
                {
                    Console.WriteLine(article.Title);
                }
            }

            IEnumerator enumerator = magazine.Articles.GetEnumerator();
            while (enumerator.MoveNext())
            {
                Article article = (Article)enumerator.Current;
                if (article.Rating > 4.3)
                {
                    Console.WriteLine(article.Title);
                }
            }

            Console.WriteLine("\nArticles with Title Containing 'AI':");
            foreach (Article article in magazine.GetArticlesByTitleSubstring("AI"))
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
