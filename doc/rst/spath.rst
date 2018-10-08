SPATH
=====

Overview
++++++++
The spath libary defines a data structure and a number of functions to manipulate paths,
including combining, slicing, simplification,
computing relative paths, and converting to/from character strings.

This object stores file paths as a linked list of path components,
where a component is a character string separated by '/' symbols.
An empty string is a valid component, and they are often found
as the first component in an absolute path, as in ``/hello/world``,
or as the last component in a path ending with '/'.
Components are indexed starting at 0.

Common functions
++++++++++++++++

This section lists the most common functions used when dealing with paths.
For a full listing, refer to comments in spath.h.
The implementation can be found in spath.c.

Creating and freeing path objects
---------------------------------
First, before using a path, one must allocate a path object::

    spath* path = spath_new();

This allocates an empty (or "null") path having 0 components. 
One must free the path when done with it::

    spath_delete(&path);

One may also create a path from a character string::

    spath* path = spath_from_str("/hello/world");

This splits the path into components at '/' characters.
In this example, the resulting path would have three components,
consisting of the empty string, ``hello``, and ``world``.
One can construct a path from a formatted string::

    spath* path = spath_from_strf("/%s/%s/%d", dir1, dir2, id);

Or to make a full copy of a path as path2::

    spath* path2 = spath_dup(path);

Querying paths and converting them to character string
------------------------------------------------------
One can determine the number of components in a path::

    int components = spath_components(path);

A shortcut is available to identify a "null" path (i.e., a path with 0 components)::

    int is_null_flag = spath_is_null(path);

This function returns 1 if the path has 0 components and 0 otherwise.
You can determine whether a path is absolute::

    int is_absolute_flag = spath_is_absolute(path);

This returns 1 if the path starts with an empty string and 0 otherwise.
The character representation of such a path starts with a '/' character
or otherwise it is the empty string.

To get the number of characters in a path::

    size_t len = spath_strlen(path);

This count includes '/' characters, but like the strlen function,
it excludes the terminating NULL character.

One can convert a path and return it as a newly allocated character string::

    char* str = spath_strdup(path);
    spath_free(&str);

The caller is responsible for freeing the returned string.

Or one can copy the path into a buffer as a character string::

    char buf[bufsize];
    spath_strcpy(buf, bufsize, path);

Combining paths
---------------
There are functions to prepend and append entries to a path.
To prepend entries of path2 to path1 (does not affect path2)::

    spath_prepend(path1, path2);

Similarly to append path2 to path1::

    spath_append(path1, path2);

Or one can insert entries of path2 into path1 at an arbitrary location::

    spath_insert(path1, offset, path2);

Here offset can be any value in the range [0, N] where N
is the number of components in path1.
With an offset of 0, the entries of path2 are inserted before the first
component of path1.
With an offset of N-1, path2 in inserted before the last component
of path1.
An offset of N inserts path2 after the last component of path1.

In addition, one may insert a string into a path
using functions ending with _str, e.g., spath_prepend_str.
One may insert a formatted string into a path using functions
ending with _strf, e.g., spath_prepend_strf.

Slicing paths
-------------
A number of functions are available to slice paths into smaller pieces.
First, one can chop components from the start and end of a path::

    spath_slice(path, offset, length);

This modifies path to keep length components starting from the specified offset.
The offset can be negative to count from the back.
A negative length means that all components are taken starting from the offset
to the end of the path.

A shortcut to chop off the last component::

    spath_dirname(path);

A shortcut that keeps only the last component::

    spath_basename(path);

The following function cuts a path in two at the specified offset.
All components starting at offset are returned as a newly allocated path.
The original path is modified to contain the beginning components::

    spath* path2 = spath_cut(path1, offset);

The above functions modify the source path.
If one wants to take a piece of a path without modifying the source,
you can use the following function.
To create a new path which is a substring of a path::

    spath* path2 = spath_sub(path, offset, length);

The offset and length values have the same meaning as in spath_slice.

Other path manipulation
-----------------------
A common need when dealing with paths is to simplify them to some reduced form.
The following function eliminates all ".", "..",
consecutive '/', and trailing '/' characters::

    spath_reduce(path);

As an example, the above function converts a path like ``/hello/world/../foo/bar/.././``
to ``/hello/foo``.

Since it is common to start from a string, reduce the path, and convert back to a string,
there is a shortcut that allocates a new, reduced path as a string::

    char* reduced_str = spath_strdup_reduce_str(str);
    spath_free(&reduced_str);

The caller is responsible for freeing the returned string.

Another useful function is to compute one path relative to another::

    spath* path = spath_relative(src, dst);

This function computes dst as a path relative to src and returns
the result as a newly allocated path object.
For example, if src is ``/hello/world`` and dst is ``/hello/foo``,
the returned path would be ``../foo``.
