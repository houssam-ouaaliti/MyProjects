<?php

namespace App\Http\Controllers;

use App\Models\Property;
use Illuminate\Http\Request;

class PropertyController extends Controller
{
    public function index()
    {
        // On récupère toutes les propriétés de la base
        $properties = Property::all();
        
        // On les envoie à la vue 'properties.index'
        return view('properties.index', compact('properties'));
    }
}
