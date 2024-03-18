using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;

public enum Update
{
    Add,
    Replace,
    Property
}



public delegate void MagazinesChangedHandler<TKey>(object source, MagazinesChangedEventArgs<TKey> args);

public class MagazinesChangedEventArgs<TKey> : EventArgs
{
    public string CollectionName { get; }
    public Update UpdateType { get; }
    public string PropertyName { get; }
    public TKey Key { get; }

    public MagazinesChangedEventArgs(string collectionName, Update updateType, string propertyName, TKey key)
    {
        CollectionName = collectionName;
        UpdateType = updateType;
        PropertyName = propertyName;
        Key = key;
    }

    public override string ToString()
    {
        return $"Collection: {CollectionName}, UpdateType: {UpdateType}, PropertyName: {PropertyName}, Key: {Key}";
    }
}

public class Edition : INotifyPropertyChanged
{
    private string editionName;
    private DateTime releaseDate;
    private int circulation;

    public string EditionName
    {
        get { return editionName; }
        set
        {
            if (value != editionName)
            {
                editionName = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(nameof(EditionName)));
            }
        }
    }

    public DateTime ReleaseDate
    {
        get { return releaseDate; }
        set
        {
            if (value != releaseDate)
            {
                releaseDate = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(nameof(ReleaseDate)));
            }
        }
    }

    public int Circulation
    {
        get { return circulation; }
        set
        {
            if (value != circulation)
            {
                circulation = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(nameof(Circulation)));
            }
        }
    }

    public event PropertyChangedEventHandler PropertyChanged;

    public override string ToString()
    {
        return $"Edition Name: {EditionName}, Release Date: {ReleaseDate.ToShortDateString()}, Circulation: {Circulation}";
    }
}

public class MagazineCollection<TKey>
{
    public string CollectionName { get; }
    private Dictionary<TKey, Magazine> collection;

    public event MagazinesChangedHandler<TKey> MagazinesChanged;

    public MagazineCollection(string collectionName)
    {
        CollectionName = collectionName;
        collection = new Dictionary<TKey, Magazine>();
    }

    public bool Replace(Magazine mold, Magazine mnew)
    {
        foreach (var kvp in collection)
        {
            if (kvp.Value == mold)
            {
                collection[kvp.Key] = mnew;
                MagazinesChanged?.Invoke(this, new MagazinesChangedEventArgs<TKey>(CollectionName, Update.Replace, "", kvp.Key));
                return true;
            }
        }
        return false;
    }

    public void Add(TKey key, Magazine magazine)
    {
        collection.Add(key, magazine);
        MagazinesChanged?.Invoke(this, new MagazinesChangedEventArgs<TKey>(CollectionName, Update.Add, "", key));
    }

    public override string ToString()
    {
        return $"Collection Name: {CollectionName}";
    }


}

public class Magazine : INotifyPropertyChanged
{
    private string magazineName;

    public string MagazineName
    {
        get { return magazineName; }
        set
        {
            if (value != magazineName)
            {
                magazineName = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(nameof(MagazineName)));
            }
        }
    }

    public event PropertyChangedEventHandler PropertyChanged;

    public override string ToString()
    {
        return $"Magazine Name: {MagazineName}";
    }
}

public class Listener
{
    private List<ListEntry> entries;

    public Listener()
    {
        entries = new List<ListEntry>();
    }

    public void HandleMagazinesChanged(object source, MagazinesChangedEventArgs<string> args)
    {
        entries.Add(new ListEntry(args.CollectionName, args.UpdateType, args.PropertyName, args.Key));
    }

    public override string ToString()
    {
        string result = "Listener Entries:\n";
        foreach (var entry in entries)
        {
            result += entry.ToString() + "\n";
        }
        return result;
    }

    private class ListEntry
    {
        public string CollectionName { get; }
        public Update UpdateType { get; }
        public string PropertyName { get; }
        public string Key { get; }

        public ListEntry(string collectionName, Update updateType, string propertyName, string key)
        {
            CollectionName = collectionName;
            UpdateType = updateType;
            PropertyName = propertyName;
            Key = key;
        }

        public override string ToString()
        {
            return $"Collection: {CollectionName}, UpdateType: {UpdateType}, PropertyName: {PropertyName}, Key: {Key}";
        }
    }
}




class Program
{
    static void Main(string[] args)
    {
        MagazineCollection<string> collection1 = new MagazineCollection<string>("Collection1");
        MagazineCollection<string> collection2 = new MagazineCollection<string>("Collection2");
        Listener listener = new Listener();

        collection1.MagazinesChanged += listener.HandleMagazinesChanged;
        collection2.MagazinesChanged += listener.HandleMagazinesChanged;

        collection1.Add("key1", new Magazine { MagazineName = "Magazine1" });
        collection1.Add("key2", new Magazine { MagazineName = "Magazine2" });

        Magazine newMagazine = new Magazine { MagazineName = "Magazine3" };


        collection2.Add("key3", new Magazine { MagazineName = "Magazine4" });

        Console.WriteLine(listener.ToString());
    }
}
