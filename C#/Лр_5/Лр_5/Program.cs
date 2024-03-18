using System;
using System.Collections.Generic;
using System.IO;
using System.Text.Json;

class Program
{
    static void Main(string[] args)
    {
        MagazineCollection<Article> magazineCollection = new MagazineCollection<Article>();
        magazineCollection.AddFromConsole();
        magazineCollection.Save("magazineCollection.json");
        Console.WriteLine("Original object:");
        Console.WriteLine(magazineCollection);
        magazineCollection.Load("magazineCollection.json");
        magazineCollection.AddFromConsole();
        magazineCollection.Save("magazineCollection.json");
        Console.WriteLine("\nObject after modification:");
        Console.WriteLine(magazineCollection);
        MagazineCollection<Article> newMagazineCollection = new MagazineCollection<Article>();
        newMagazineCollection.Load("magazineCollection.json");
        newMagazineCollection.AddFromConsole();
    }
}

class MagazineCollection<T> where T : IDeepCopy<T>, new()
{
    private List<T> items = new List<T>();
    public bool AddFromConsole()
    {
        try
        {
            Console.WriteLine("Enter data for the new item (format: title, author, rating):");
            string[] input = Console.ReadLine().Split(',');
            string title = input[0].Trim();
            string author = input[1].Trim();
            int rating = int.Parse(input[2].Trim());
            T newItem = new T();
            (newItem as Article).Title = title;
            (newItem as Article).Author = author;
            (newItem as Article).Rating = rating;
            items.Add(newItem);
            return true;
        }
        catch (Exception e)
        {
            Console.WriteLine("Error: " + e.Message);
            return false;
        }
    }


    public bool Save(string filename)
    {
        try
        {
            string jsonString = JsonSerializer.Serialize(this);
            File.WriteAllText(filename, jsonString);
            return true;
        }
        catch (Exception e)
        {
            Console.WriteLine("Error: " + e.Message);
            return false;
        }
    }


    public bool Load(string filename)
    {
        try
        {
            string jsonString = File.ReadAllText(filename);
            MagazineCollection<T> newCollection = JsonSerializer.Deserialize<MagazineCollection<T>>(jsonString);
            this.items = newCollection.items;
            return true;
        }
        catch (Exception e)
        {
            Console.WriteLine("Error: " + e.Message);
            return false;
        }
    }

    public override string ToString()
    {
        string result = "";
        foreach (var item in items)
        {
            result += item.ToString() + "\n";
        }
        return result;
    }
}

class Article : IDeepCopy<Article>
{
    public string Title { get; set; }
    public string Author { get; set; }
    public int Rating { get; set; }

    public Article DeepCopy()
    {
        Article newArticle = new Article();
        newArticle.Title = this.Title;
        newArticle.Author = this.Author;
        newArticle.Rating = this.Rating;
        return newArticle;
    }

    public override string ToString()
    {
        return $"Title: {Title}, Author: {Author}, Rating: {Rating}";
    }
}

interface IDeepCopy<T>
{
    T DeepCopy();
}
