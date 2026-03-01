<?php

namespace Database\Seeders;

use Illuminate\Database\Console\Seeds\WithoutModelEvents;
use Illuminate\Database\Seeder;

class PropertySeeder extends Seeder
{
    /**
     * Run the database seeds.
     */
    public function run(): void
    {
        \App\Models\Property::create([
            'name' => 'Villa avec vue sur mer',
            'description' => 'Une magnifique villa située au bord de l\'eau.',
            'price_per_night' => 150.00
        ]);

        \App\Models\Property::create([
            'name' => 'Appartement Moderne',
            'description' => 'Un loft en plein centre-ville.',
            'price_per_night' => 85.50
        ]);
    }
}
